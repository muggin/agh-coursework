package models

import akka.actor.{Actor, UntypedActor, ActorRef}
import protocols.ExampleProtocol.{ExamplePacket, ExampleHeader, ExampleData}
import protocols.IPv4.Ipv4Address

/**
 * Created by Wojtek on 07/06/15.
 */

class Endpoint(ipAddress: Ipv4Address) extends Actor with akka.actor.ActorLogging {
  private val endpointName = self.path.name
  private var otherSide: ActorRef = _

  def connectTo(interface: ActorRef) = {
    otherSide = interface
  }

  def sendMessage(message: String, destination: Ipv4Address) = {
    val header = ExampleHeader(ipAddress, destination)
    val body = ExampleData(message)
    val packet = ExamplePacket(header, body)

    otherSide ! ExchangePacket(packet)
  }

  override def receive = {
    case ConnectInterface(externalInterface: ActorRef) => {
      sendLog(s"Connecting to interface: ${externalInterface}")
        otherSide = externalInterface
    }

    case SendMessage(message, destination) => {
      sendLog(s"Sending message to: ${destination}")
      sendMessage(message, destination)
    }

    case ExchangePacket(packet) => {
      sendLog(s"Received message: '${packet.exampleData.payload}' from: ${packet.exampleHeader.source}")
      println()
    }
  }

  def sendLog(logMsg: String) = {
    log.info(s"[Endpoint ${endpointName}] - " + logMsg)
  }
}
