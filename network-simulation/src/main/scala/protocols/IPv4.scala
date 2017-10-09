package protocols

import protocols.api.{PacketData, PacketHeader, Packet}


/** Internet Protocol version 4 (IPv4) */
object IPv4 {

  /** IPv4 Packet */
  class Ipv4Packet(val header: Ipv4Header, val data: Ipv4Data) extends Packet {

  }

  /** IPv4 Packet Header */
  class Ipv4Header extends PacketHeader {

  }

  /** IPv4 Packet Data */
  class Ipv4Data extends PacketData {

  }

  /** IPv4 Address */
  case class Ipv4Address(a: Short = 0, b: Short = 0, c: Short = 0, d: Short= 0) {
    override def toString = s"$a.$b.$c.$d"
  }

}