/**
 * @file    echoTSB.cpp
 * @brief   TSB example
 * @author  
 */

#include <tsb/TSBTypes.h>
#include <iostream>

using namespace std;


int main(int argc,char** argv)
{
  // read the document

  TSBDocument *document = readTSBFromFile("tsb_example.xml");

  // TODO: document has no printerrors function ... it should
  //if (document->getNumErrors(LIBLX_SEV_ERROR) > 0)
  //  document->printErrors();

  cout << "Document contains " << document->getNumComments() << " comments:\n";
  for (unsigned int i = 0; i < document->getNumComments(); ++i)
  {
    TSBComment *comment = document->getComment(i);
    cout << "Comment #" << comment->getNumber() << endl;
    cout << "Author " << comment->getContributor() << endl;
    cout << "\"" << comment->getPoint() << "\"" << endl;
  }

  string text = writeTSBToStdString(document);
  cout << text;

  delete document;
}
