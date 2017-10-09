package models

import akka.actor.ActorRef
import protocols.ExampleProtocol.ExamplePacket
import protocols.IPv4.Ipv4Address

/**
 * Router Management Messages
 */
trait RouterManagementMessage
/** Message sent to [[Router]] in order to enter Configuration state */
case object EnterConfigurationMode extends RouterManagementMessage

/** Message sent to [[Router]] in order to leave Configuration state */
case object LeaveConfigurationMode extends RouterManagementMessage


/** Message sent to [[Router]] in order to configure the chosen interface address */
case class SetupInterface(interfaceName: String, ipAddress: Ipv4Address, networkSubmask: Ipv4Address) extends RouterManagementMessage

/** Message sent to [[Router]] in order to configure the default gateway address */
case class SetupDefaultGateway(interfaceName: String) extends RouterManagementMessage


/**
 * Router Operation Messages
 */
trait RouterOperationMessage
case class RoutePacket(packet: ExamplePacket) extends RouterOperationMessage


/**
 * Network Interface Management Messages
 */
trait InterfaceManagementMessage

/** Message sent to [[NetworkInterface]] when a new connection is established */
case class ConnectInterface(externalInterface: ActorRef) extends InterfaceManagementMessage

/** Message sent to [[NetworkInterface]] when a connection is broken */
case class DisconnectInterface(externalInterface: ActorRef) extends InterfaceManagementMessage

/**  Message sent to [[NetworkInterface]] in order to setup it's IP address */
case class SetIpAddress(ipv4Address: Ipv4Address) extends InterfaceManagementMessage


/**
 * Interface Operation Messages between interfaces in the same [[Router]]
 */
trait InternalInterfaceOperationMessage

/** Message sent to [[NetworkInterface]] containing an outgoing packet */
case class SendPacket(packet: ExamplePacket) extends InternalInterfaceOperationMessage

/**
 * Interface Operation Messages between interfaces in different [[Router]]
 */
trait ExternalInterfaceOperationMessage

/** Message sent to [[NetworkInterface]] containing an incoming packet */
case class ExchangePacket(packet: ExamplePacket) extends ExternalInterfaceOperationMessage

/**
 *
 */
trait EndpointOperationMessage

case class SendMessage(message: String, destination: Ipv4Address) extends EndpointOperationMessage