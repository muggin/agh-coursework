import akka.actor.{ActorRef, Inbox, ActorSystem, Props}
import com.typesafe.config.ConfigFactory
import models._
import protocols.ExampleProtocol._
import protocols.IPv4.Ipv4Address
import scala.concurrent.Await
import scala.concurrent.duration._
import akka.event.{LoggingAdapter, Logging, DiagnosticLoggingAdapter}
/**
 * Created by Wojtek on 30/05/15.
 */

object Main extends App {

  val system = ActorSystem("NetworkSimulation", ConfigFactory.load.getConfig("akka"))
  val systemLogger: LoggingAdapter = Logging.getLogger(system, this)
  sendLog("Starting Actor System")

  val router1 = system.actorOf(Props[Router], name = "r1")
  val router2 = system.actorOf(Props[Router], name = "r2")
  val router3 = system.actorOf(Props[Router], name = "r3")

  val endpoint1 = system.actorOf(Props(classOf[Endpoint], Ipv4Address(192, 168, 2, 5)), name = "e1")
  val endpoint2 = system.actorOf(Props(classOf[Endpoint], Ipv4Address(192, 168, 7, 15)), name = "e2")
  Thread.sleep(1500)

  // Open Router Terminal
  val inbox: Inbox = Inbox.create(system)

  sendLog("Configuring routers")
  //
  // Configure Router 1
  //
  // Enter configuration mode
  inbox.send(router1, EnterConfigurationMode)

  // Configure interface NIC1 -> IP: 192.168.0.1
  inbox.send(router1, SetupInterface("NIC1", Ipv4Address(192, 168, 1, 1), Ipv4Address(255, 255, 255, 0)))
  val r1n1: ActorRef = Await.result(system.actorSelection("user/r1nic1").resolveOne()(2.seconds), 2.seconds)

  // Configure interface NIC2 -> IP: 192.168.1.1
  inbox.send(router1, SetupInterface("NIC2", Ipv4Address(192, 168, 2, 1), Ipv4Address(255, 255, 255, 0)))
  val r1n2: ActorRef = Await.result(system.actorSelection("user/r1nic2").resolveOne()(2.seconds), 2.seconds)

  // Configure interface NIC3 -> IP: 192.168.3.1
  inbox.send(router1, SetupInterface("NIC3", Ipv4Address(192, 168, 3, 1), Ipv4Address(255, 255, 255, 0)))
  val r1n3: ActorRef = Await.result(system.actorSelection("user/r1nic3").resolveOne()(2.seconds), 2.seconds)

  // Configure default gateway
  inbox.send(router1, SetupDefaultGateway("NIC1"))

  // Leave configuration mode
  inbox.send(router1, LeaveConfigurationMode)

  //
  // Configure Router 2
  //
  // Enter configuration mode
  inbox send(router2, EnterConfigurationMode)

  // Configure interface NIC1 -> IP: 192.168.0.1
  inbox send(router2, SetupInterface("NIC1", Ipv4Address(192, 168, 1, 254), Ipv4Address(255, 255, 255, 0)))
  val r2n1: ActorRef = Await.result(system.actorSelection("user/r2nic1").resolveOne()(2.seconds), 2.seconds)

  // Configure interface NIC2 -> IP: 192.168.1.11
  inbox send(router2, SetupInterface("NIC2", Ipv4Address(192, 168, 4, 254), Ipv4Address(255, 255, 255, 0)))
  val r2n2: ActorRef = Await.result(system.actorSelection("user/r2nic2").resolveOne()(2.seconds), 2.seconds)

  // Configure interface NIC3 -> IP: 192.168.3.1
  inbox send(router2, SetupInterface("NIC3", Ipv4Address(192, 168, 5, 254), Ipv4Address(255, 255, 255, 0)))
  val r2n3: ActorRef = Await.result(system.actorSelection("user/r2nic3").resolveOne()(2.seconds), 2.seconds)

  // Configure default gateway
  inbox send(router2, SetupDefaultGateway("NIC3"))

  // Leave configuration mode
  inbox send(router2, LeaveConfigurationMode)

  //
  // Configure Router 3
  //
  // Enter configuration mode
  inbox send(router3, EnterConfigurationMode)

  // Configure interface NIC1 -> IP: 192.168.0.1
  inbox send(router3, SetupInterface("NIC1", Ipv4Address(192, 168, 5, 254), Ipv4Address(255, 255, 255, 0)))
  val r3n1: ActorRef = Await.result(system.actorSelection("user/r3nic1").resolveOne()(2.seconds), 2.seconds)

  // Configure interface NIC2 -> IP: 192.168.1.11
  inbox send(router3, SetupInterface("NIC2", Ipv4Address(192, 168, 6, 254), Ipv4Address(255, 255, 255, 0)))
  val r3n2: ActorRef = Await.result(system.actorSelection("user/r3nic2").resolveOne()(2.seconds), 2.seconds)

  // Configure interface NIC3 -> IP: 192.168.3.1
  inbox send(router3, SetupInterface("NIC3", Ipv4Address(192, 168, 7, 254), Ipv4Address(255, 255, 255, 0)))
  val r3n3: ActorRef = Await.result(system.actorSelection("user/r3nic3").resolveOne()(2.seconds), 2.seconds)

  // Configure default gateway
  inbox send(router3, SetupDefaultGateway("NIC1"))

  // Leave configuration mode
  inbox send(router3, LeaveConfigurationMode)

  sendLog("Connecting router interfaces")
  // Connecting Network Interfaces of distinct Routers
  inbox send(r1n1, ConnectInterface(r2n1))
  inbox send(r2n1, ConnectInterface(r1n1))

  inbox send(r2n3, ConnectInterface(r3n1))
  inbox send(r3n1, ConnectInterface(r2n3))

  // Connecting Network Interfaces to Endpoints
  inbox send(r1n2, ConnectInterface(endpoint1))
  inbox send(endpoint1, ConnectInterface(r1n2))

  inbox send(r3n3, ConnectInterface(endpoint2))
  inbox send(endpoint2, ConnectInterface(r3n3))

  sendLog("Testing connection")
  endpoint1 ! SendMessage("Test Message", Ipv4Address(192, 168, 15, 15))

//
//  inbox send(r1n2, ExchangePacket(packet))

  def sendLog(logMsg: String) = {
    systemLogger.info("[ADMIN] - " + logMsg)
  }
}