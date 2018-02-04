#pragma once

#ifdef __cplusplus
extern "C" {
#endif //#ifdef __cplusplus__

void drawScrollBar(WINDOW * inputWindow, int numberOfLinesToShow, 
    int numberOfLines, int firstLineToShow, int horizontalIndexForScrollBar);

#ifdef __cplusplus
}
#endif //#ifdef __cplusplus__
