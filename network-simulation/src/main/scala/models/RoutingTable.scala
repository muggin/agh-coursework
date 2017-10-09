package models

import akka.actor.ActorRef
import protocols.IPv4.Ipv4Address
/**
 * Created by Wojtek on 31/05/15.
 */
class RoutingTable() {
  var routes: List[Route] = List()
  var defaultGateway: Route = Route(Ipv4Address(0, 0, 0, 0), Ipv4Address(255, 255, 255, 255), null, 99)

  def addRoute(interfaceAddress: Ipv4Address, networkMask: Ipv4Address, interface: ActorRef) = {
    routes = Route(interfaceAddress, networkMask, interface, 1) :: routes
  }

  def removeRoute(modifiedInterface: ActorRef) = {
//    val removedIndex = routes.indexWhere { route =>
//      route.interface == modifiedInterface
//    }
//
//    routes = routes.
  }

  def configureDefaultGateway(gatewayAddress: Ipv4Address, interface: ActorRef) = {
    defaultGateway = Route(Ipv4Address(0, 0, 0, 0), Ipv4Address(0, 0, 0, 0), interface, 30)
  }

  def findRoute(destination: Ipv4Address): ActorRef = {
    routes.foldLeft(defaultGateway) { (bestRoute, currentRoute) =>
      if (distance(bestRoute, destination) > distance(currentRoute, destination))
        currentRoute
      else
        bestRoute
    }.interface
  }

  def distance(route: Route, destination: Ipv4Address): Int = {
    route.networkMask match {
      case Ipv4Address(255, 255, 255, 255) =>
        if (route.destination == destination) {
          1
        } else {
          99
        }
      case Ipv4Address(255, 255, 255, _) =>
        if (route.destination.a == destination.a &&
            route.destination.b == destination.b &&
            route.destination.c == destination.c) {
          2
        } else {
          99
        }
      case Ipv4Address(255, 255, _, _) =>
        if (route.destination.a == destination.a &&
          route.destination.b == destination.b) {
          3
        } else {
          99
        }
      case Ipv4Address(255, _, _, _) =>
        if (route.destination.a == destination.a) {
          4
        } else {
          99
        }
      case Ipv4Address(_, _, _, _) =>
        5
    }
  }

  case class Route(destination: Ipv4Address, networkMask: Ipv4Address, interface: ActorRef, metric: Int) extends Ordered[Route] {

    override def compare(that: Route) = {
      this.metric.compare(that.metric)
    }
  }
}