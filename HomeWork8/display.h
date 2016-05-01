/*
 * File:    $Id: display.h,v 1.3 2014/12/06 03:04:20 csci243 Exp $
 *
 * Author:  Margaret Reek
 * Contributors: idea borrowed from Neill Graham book, and enhanced
 *      by James Heliotis
 *
 * Description:
 *      Manipulate the display and the cursor in the display.
 *      ANSI character sequences are used to achieve this.
 *      A future version may use the curses library.
 */

#ifndef RITCSFIGURES_DISPLAY_H
#define RITCSFIGURES_DISPLAY_H


/// Clear the terminal window of all characters.
/// 
/// Side Effects
///   The terminal window display is modified.
///   The cursor moves to the lower left of the terminal.
///
void clear();

/// Cause a character to appear at the current position of the cursor.
///
/// Arguments
///   character: the character to be shown
///
/// Side Effects
///   The cursor advances to the next position in the row.
///   The terminal window display is modified.
///
void put( char character );

/// Move the cursor to position specified.
/// No visible display changes, but the cursor is modified.
/// The coordinate system is unusual: the leftmost column is 0, but
/// the topmost row is 1. Coordinate values increase rightward and downward.
/// The uppermost cursor position is therefore (row=1, column=0).
///
/// Arguments
///   rCursor: the destination row
///   cCursor: the destination column
/// 
void set_cur_pos( int rCursor, int cCursor);

#endif
