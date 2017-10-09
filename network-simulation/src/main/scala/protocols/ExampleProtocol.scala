package protocols

import protocols.IPv4._

/** ExampleProtocol is a simplified version of the Internet Protocol (IP) */
object ExampleProtocol {

  /** ExampleProtocol Packet */
  case class ExamplePacket(exampleHeader: ExampleHeader, exampleData: ExampleData) extends Ipv4Packet(exampleHeader, exampleData)

  /** ExampleProtocol Packet Header */
  case class ExampleHeader(source: Ipv4Address,
                      destination: Ipv4Address,
                      ttl: Int = 5) extends Ipv4Header

  /** ExampleProtocol Packet Data */
  case class ExampleData(payload: String) extends Ipv4Data
}