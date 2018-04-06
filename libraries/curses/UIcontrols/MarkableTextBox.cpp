
#include "MarkableTextBox.hpp"

namespace curses {

MarkableTextBox::MarkableTextBox(chtype colorPair, chtype markColorPair)
  : curses::TextBox(colorPair),
    m_markColorPair(markColorPair)
{
  
}

/** @param currentLine : the window line */
void MarkableTextBox::HandleCurrentLine(
  const HandleCurrentLineParams & handleCurrentLineParams
  )
{
  const int charIndexOfTextLineBegin = handleCurrentLineParams.p_textLineBegin
    - m_content.c_str();
  
  unsigned charIndexOfWindowLineBegin = 
    handleCurrentLineParams.p_windowLineBegin - m_content.c_str();
  int currentCharPos = charIndexOfWindowLineBegin;
  int numCharsToPrint;
  int currentX = 0;
  chtype currentColor;
  bool insideMark = false;
  int numRemainingCharsToPrintForWindowLine = handleCurrentLineParams.numCharsToPrint;
  
  markPositionsType::const_iterator markPositionsIter = m_markPositions.begin();
  markPositionsType::const_iterator markPositionAfterCurrentCharPos  = m_markPositions.end();
  for(; markPositionsIter != m_markPositions.end() ; markPositionsIter ++)
  {
    const Mark & mark = *markPositionsIter;
    unsigned markEnd = mark.getMarkEnd();
    /** Mark from previous line. */
    if( markEnd > currentCharPos &&
        mark.begin < currentCharPos)
    {
        setcolor(m_windowHandle, m_markColorPair);
        numCharsToPrint = markEnd - charIndexOfWindowLineBegin;
        insideMark = true;
//        break;
    }
    if( mark.begin >= currentCharPos && 
        /*markEnd <=*/ mark.begin < charIndexOfWindowLineBegin + 
        numRemainingCharsToPrintForWindowLine)
    {
      markPositionAfterCurrentCharPos = markPositionsIter;
//      setcolor(m_windowHandle, m_colorPair);
//      numCharsToPrint = mark.begin - charIndexOfWindowLineBegin;
      break;
    }
  }
//  if( ! insideMark && markPositionAfterCurrentCharPos == m_markPositions.end() )
//  {
//    setcolor(m_windowHandle, m_colorPair);
//    numCharsToPrint = handleCurrentLineParams.numCharsToPrint;
//  }
  if( insideMark)
  {
    if( numCharsToPrint > numRemainingCharsToPrintForWindowLine)
      numCharsToPrint = numRemainingCharsToPrintForWindowLine;
    mvwaddnstr(m_windowHandle,
      handleCurrentLineParams.windowLineNumber + m_drawBorder /** y position*/, 
      currentX + m_drawBorder /** x position */, 
      m_content.c_str() + charIndexOfWindowLineBegin /** string */, 
      numCharsToPrint /** max number of chars */);
    currentX += numCharsToPrint;
    numRemainingCharsToPrintForWindowLine -= numCharsToPrint;
  }
//  if( markPositionAfterCurrentCharPos != m_markPositions.end() )
//  {
//    setcolor(m_windowHandle, m_colorPair);
//    const Mark & mark = *markPositionAfterCurrentCharPos;
//    numCharsToPrint = mark.begin - charIndexOfWindowLineBegin;
//    if( numCharsToPrint > handleCurrentLineParams.numCharsToPrint)
//      numCharsToPrint = handleCurrentLineParams.numCharsToPrint;
//    
//    mvwaddnstr(m_windowHandle,
//      handleCurrentLineParams.windowLineNumber + m_drawBorder /** y position*/, 
//      currentX + m_drawBorder /** x position */, 
//      m_content.c_str() + charIndexOfWindowLineBegin /** string */, 
//      numCharsToPrint /** max number of chars */);
//  }
  for( ; markPositionAfterCurrentCharPos != m_markPositions.end() ; 
          markPositionAfterCurrentCharPos ++)
  {
    const Mark & mark = *markPositionAfterCurrentCharPos;
    /** If mark lies in current line. */
    if( mark.begin >= charIndexOfWindowLineBegin + currentX && mark.begin < 
        charIndexOfWindowLineBegin + /*numRemainingCharsToPrintForWindowLine*/
        handleCurrentLineParams.numCharsToPrint )
    {
//      markPositionAfterCurrentCharPos = markPositionsIter;
      setcolor(m_windowHandle, m_colorPair);
      numCharsToPrint = mark.begin - (charIndexOfWindowLineBegin + currentX);
      
      if( numCharsToPrint > numRemainingCharsToPrintForWindowLine)
        numCharsToPrint = numRemainingCharsToPrintForWindowLine;

    mvwaddnstr(m_windowHandle,
      handleCurrentLineParams.windowLineNumber + m_drawBorder /** y position*/, 
      currentX + m_drawBorder /** x position */, 
      m_content.c_str() + charIndexOfWindowLineBegin + currentX /** string */, 
      numCharsToPrint /** max number of chars */);
    currentX += numCharsToPrint;
    numRemainingCharsToPrintForWindowLine -= numCharsToPrint;
    
    
     numCharsToPrint = mark.length;
      if( numCharsToPrint > numRemainingCharsToPrintForWindowLine)
        numCharsToPrint = numRemainingCharsToPrintForWindowLine;
       
        setcolor(m_windowHandle, m_markColorPair);
        mvwaddnstr(m_windowHandle,
          handleCurrentLineParams.windowLineNumber + m_drawBorder /** y position*/, 
          currentX + m_drawBorder /** x position */, 
          m_content.c_str() + charIndexOfWindowLineBegin + currentX /** string */, 
          numCharsToPrint /** max number of chars */);
        currentX += numCharsToPrint;
        numRemainingCharsToPrintForWindowLine -= numCharsToPrint;
    }
    else
        break;
//    if( mark.getMarkEnd() )
  }
  /** Either no mark in curren window line. */
  if( numRemainingCharsToPrintForWindowLine > 0 )
  {
    setcolor(m_windowHandle, m_colorPair);
    mvwaddnstr(m_windowHandle,
      handleCurrentLineParams.windowLineNumber + m_drawBorder /** y position*/, 
      currentX + m_drawBorder /** x position */, 
      m_content.c_str() + charIndexOfWindowLineBegin + currentX /** string */, 
      numRemainingCharsToPrintForWindowLine /** max number of chars */);
  }
  
//    currentX += numCharsToPrint;
//            
//    const int windowLineBeginCharPos = handleCurrentLineParams.
//      p_windowLineBegin - m_content.c_str();
//    const int windowLineEndCharPos = windowLineBeginCharPos + 
//      handleCurrentLineParams.numCharsToPrint;
//
////    int currentX = m_drawBorder;
//    int numCharsToPrint = handleCurrentLineParams.numCharsToPrint;
//    const char * p_currentChar = handleCurrentLineParams.p_windowLineBegin;
//    
//    if( charIndexOfTranslationAttributeValue > windowLineBeginCharPos &&
//      charIndexOfTranslationAttributeValue < windowLineEndCharPos)
//    {
//      const int numCharsWithDefaultColor = 
//        charIndexOfTranslationAttributeValue - windowLineBeginCharPos;
//
//      setcolor(m_windowHandle, m_colorPair);
//      mvwaddnstr(m_windowHandle,
//        handleCurrentLineParams.windowLineNumber /** y position*/, 
//        currentX /** x position */, 
//        m_content.c_str() + windowLineBeginCharPos /** string */, 
//        numCharsWithDefaultColor /** max number of chars */);
//      currentX += numCharsWithDefaultColor;
//    }   
//  }
}

}/** namespace curses*/

