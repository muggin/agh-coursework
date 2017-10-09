package node;

import node.interfaces.MRNode;

/**
 * Created by Wojtek on 18/02/15.
 */
public class RegisteredNode extends NodeDecorator implements Comparable<RegisteredNode> {
    private int scheduledJobs = 0;
    private int finishedJobs = 0;
    double nodeRank = 1;

    public RegisteredNode(MRNode node) {
        super(node);
    }

    public void calculateRank() {
        nodeRank = finishedJobs / scheduledJobs;
    }

    public void incrementAssignCounter() {
        ++scheduledJobs;
        calculateRank();
    }

    public void incrementFinishedCounter() {
        ++finishedJobs;
        calculateRank();
    }

    @Override
    public int compareTo(RegisteredNode o) {
        if (this.nodeRank == o.nodeRank)
            return 0;
        else
            return (this.nodeRank > o.nodeRank) ? -1 : 1;
    }
}
