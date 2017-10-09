name := "Network_Simulation"

version := "1.0"

scalaVersion := "2.11.6"

libraryDependencies ++= Seq(
  // Change this to another test framework if you prefer
  "org.scalatest" %% "scalatest" % "2.1.6" % "test",
  // Akka
  "com.typesafe.akka" %% "akka-actor" % "2.3.5",
  "com.typesafe.akka" %% "akka-remote" % "2.3.5",
  "com.typesafe.akka" %% "akka-testkit" % "2.3.5"
)

libraryDependencies += "ch.qos.logback" % "logback-classic" % "1.1.2"

libraryDependencies += "com.typesafe.akka" %% "akka-slf4j" % "2.3.6"



//lazy val logback = "ch.qos.logback" % "logback-classic" % "1.0.0" % "runtime"

    