package protocols.api

/**
 * Created by Wojtek on 30/05/15.
 */

/** Trait represents packet headers */
trait PacketHeader

/** Trait represents packet data */
trait PacketData

/** Trait represents a network packet */
trait Packet extends PacketData {
  def header: PacketHeader
  def data: PacketData
}