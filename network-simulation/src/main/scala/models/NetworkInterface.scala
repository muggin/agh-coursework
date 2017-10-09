package models

import akka.actor.{ActorRef, FSM}
import akka.util.Timeout
import protocols.ExampleProtocol.{ExamplePacket, ExampleHeader}
import protocols.IPv4.Ipv4Address
import scala.concurrent.duration._
import scala.concurrent.ExecutionContext.Implicits.global


/** Network Interface model implemented as an Akka FSM
  *
  * Possible states:
  * Connected - device is connected to an external Network Interface
  * Disconnected - device isn't connected to an external Network Interface
 */
class NetworkInterface(val router: ActorRef, var ipAddress: Ipv4Address) extends FSM[InterfaceState, InterfaceData] {
  implicit val timeout = Timeout(1 seconds)
  private val interfaceName = self.path.name
  private val routerName = router.path.name

  when(Disconnected) {
    case Event(ConnectInterface(externalInterface), _) => {
      goto(Connected) using InitializedInterface(externalInterface)
    }

    case _ => stay using stateData
  }

  when(Connected) {
    case Event(ExchangePacket(packet), _) => {
      val packetSource = packet.exampleHeader.source
      val packetDestination = packet.exampleHeader.destination

      // Pass incoming message to Router
      if (packet.exampleHeader.ttl > 0) {
        sendLog(s"Handling exchange packet from: ${packetSource} to: ${packetDestination}")
        val newHeader = ExampleHeader(packet.exampleHeader.source,
          packet.exampleHeader.destination,
          packet.exampleHeader.ttl - 1)
        router ! RoutePacket(ExamplePacket(newHeader, packet.exampleData))
      } else {
        sendLog(s"Dropping exchange packet from: ${packetSource} to: ${packetDestination}. TTL = 0")
      }

      // Stay in Connected state after sending packet
      stay using stateData
    }

    case Event(SendPacket(packet), interfaceState: InitializedInterface) => {
      val packetSource = packet.exampleHeader.source
      val packetDestination = packet.exampleHeader.destination
      //sendLog(s"Sending exchange packet from: ${packetSource} to: ${packetDestination}")

      // Send packet to a connected Interface
      interfaceState.otherSide ! ExchangePacket(packet)

      // Stay in Connected state after sending packet
      stay using stateData
    }

    case Event(DisconnectInterface, _) => {
      //sendLog("> [State: Disconnected]")

      // Switch to Disconnected state
      goto(Disconnected) using UninitializedInterface
    }

    case _ => stay using stateData
  }

  whenUnhandled {
    case Event(SetIpAddress(ipAddress), _) => {
      //sendLog(s"Setting IP address to: $ipAddress")

      // Set IP address of Interface
      this.ipAddress = ipAddress

      // Stay in Connected state after setting IP address
      stay using stateData
    }
  }

  def sendLog(logMsg: String) = {
    log.info(s"[Interface ${this.interfaceName}@${this.routerName}][State: ${stateName.toString}] - " + logMsg)
  }

  // Start Interface in Disconnected state with Uninitialized memory
  startWith(Disconnected, UninitializedInterface)

  initialize()
}

/** Interface/Actor States */
sealed trait InterfaceState
case object Disconnected extends InterfaceState
case object Connected extends InterfaceState

/** Interface/Actor Data */
sealed trait InterfaceData
case object UninitializedInterface extends InterfaceData
final case class InitializedInterface(otherSide: ActorRef) extends InterfaceData