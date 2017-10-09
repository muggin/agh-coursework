package models

import akka.actor.{LoggingFSM, ActorRef, Props}
import protocols.IPv4.Ipv4Address
import scala.concurrent.duration._
import scala.collection.parallel.immutable

/** Router model implemented as a Akka FSM
  *
  * Possible states:
  * Booting - device is starting up. Creating and setting up Network Interfaces.
  * Configuration - device is being configured.
  * Active - device is working.
 */
class Router extends LoggingFSM[RouterState, RouterData] {
  private var networkInterfaces: Map[String, ActorRef] = Map()
  private val routingTable: RoutingTable = new RoutingTable
  private val routerName = self.path.name

  onTransition {
    case _ -> Configuration =>
      sendLog("> [State: Configuration]")

    case Booting -> _ =>
      sendLog("Booting finished")

    case _ -> Active =>
      sendLog("> [State: Active]")
  }

  // Router in Booting state
  when(Booting, stateTimeout = 1 seconds) {
    //Event(msg: Any, data: D)
    case Event(StateTimeout, _) =>
      goto(Active) using stateData
  }

  // Router in Configuration state
  when(Configuration) {

    case Event(SetupInterface(name, ipAddress, _), _) => {
      sendLog(s"Setting interface $name to IP: ${ipAddress.toString}")
      networkInterfaces.get(name).foreach { interfaceActor =>
        interfaceActor ! SetIpAddress(ipAddress)
        routingTable.addRoute(ipAddress, Ipv4Address(255, 255, 255, 0), interfaceActor)
        sender ! interfaceActor
      }
      stay using stateData


    }

    case Event(SetupDefaultGateway(interfaceName), _) => {
      sendLog(s"Setting interface $interfaceName as Default Gateway")
      networkInterfaces.get(interfaceName).foreach { interfaceActor =>
        routingTable.configureDefaultGateway(null, interfaceActor)
        sender ! interfaceActor
      }

      stay using stateData
    }

    //
    case Event(LeaveConfigurationMode, _) =>
      goto(Active) using stateData
  }

  // Router in Active state
  when(Active) {
    //
    case Event(RoutePacket(packet), _) => {
      val packetSource = packet.exampleHeader.source
      val packetDistination = packet.exampleHeader.destination
      sendLog(s"Routing packet from: ${packetSource} to: ${packetDistination}")

      val destinationInterface = routingTable.findRoute(packet.exampleHeader.destination)
      destinationInterface ! SendPacket(packet)

      stay using stateData
    }

    case Event(EnterConfigurationMode, _) => {
      goto(Configuration) using stateData
    }
  }

  // Setup Network Interface (actors).
  // This method is called when the actor is first created
  override def preStart() = {
    networkInterfaces =  Map(
      "NIC1" -> context.system.actorOf(Props(classOf[NetworkInterface], self, Ipv4Address(0, 0, 0, 0)), name = s"${routerName}nic1"),
      "NIC2" -> context.system.actorOf(Props(classOf[NetworkInterface], self, Ipv4Address(0, 0, 0, 0)), name = s"${routerName}nic2"),
      "NIC3" -> context.system.actorOf(Props(classOf[NetworkInterface], self, Ipv4Address(0, 0, 0, 0)), name = s"${routerName}nic3"),
      "NIC4" -> context.system.actorOf(Props(classOf[NetworkInterface], self, Ipv4Address(0, 0, 0, 0)), name = s"${routerName}nic4")
    )
    sendLog("Loading ROUTER OS")
  }

  def sendLog(logMsg: String) = {
    log.info(s"[Router ${this.routerName}][State: ${stateName.toString}] - " + logMsg)
  }

  // Settings initial state to Booting with Unitialized data
  //  LoggingFSM[RouterState, RouterData]
  startWith(Booting, UninitializedRouter)

  // perform the transition into the initial state and set up timers (if required).
  initialize()
}

/** Router actor States */
sealed trait RouterState
case object Booting extends RouterState
case object Configuration extends RouterState
case object Active extends RouterState

/** Router actor Data */
sealed trait RouterData
case object UninitializedRouter extends RouterData
final case class InitializedRouter(interfaces: immutable.ParSet[NetworkInterface], routingTable: RoutingTable) extends RouterData