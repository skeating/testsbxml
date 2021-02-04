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

  TSBComment* model=document->createComment();

  // TODO: document has no printerrors function ... it should
  //if (document->getNumErrors(LIBSBML_SEV_ERROR) > 0)
  //  document->printErrors();
  
  writeTSBToFile(document,"tsb_example1.xml");
  delete document;
}
