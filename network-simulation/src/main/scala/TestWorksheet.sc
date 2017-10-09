import akka.actor.ActorRef
import protocols.IPv4.Ipv4Address

case class Route(destination: Ipv4Address, interface: ActorRef, metric: Int)

var routes: List[Route] = List(Route(Ipv4Address(0,0,0,0), ActorRef.noSender, 1),
                              Route(Ipv4Address(0,0,0,1), ActorRef.noSender, 1),
                              Route(Ipv4Address(0,0,0,2), ActorRef.noSender, 1))

val r = Ipv4Address


case class TestClass(a: Int, b: Int, c: Int)

val testA = TestClass(1,2,3)
val testB = TestClass(1,2,4)

testA == testB

val a: Int = 255
a.^(0)
