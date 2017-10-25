#include "extqcpstatisticalbox.h"

ExtQCPStatisticalBox::ExtQCPStatisticalBox (QCPAxis *keyAxis, QCPAxis *valueAxis):QCPStatisticalBox(keyAxis,valueAxis)
{

}


void ExtQCPStatisticalBox::blockinfo(bool on)
{
    if(on)
    {
         QMessageBox::about ( 0, "Task info","Task start: "+QString::number(minimum())+"\nTask time: "+QString::number(maximum()-minimum()) );
    }
    setSelected(false);
}
