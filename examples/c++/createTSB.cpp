/**
 * @file    createTSB.cpp
 * @brief   TSB example
 * @author  
 */

#include <tsb/TSBTypes.h>


int main(int argc,char** argv)
{
  // create the document

  TSBDocument *document = new TSBDocument(1,1);

  // create a Comment

  TSBComment* comment = document->createComment();

  // add attributes to comment

  comment->setContributor("Joe Bloggs");
  comment->setNumber(1.34);
  comment->setPoint("This is irrelevant");

  // TODO: document has no printerrors function ... it should
  //if (document->getNumErrors(LIBLX_SEV_ERROR) > 0)
  //  document->printErrors();

  writeTSBToFile(document,"tsb_example.xml");
  delete document;
}
