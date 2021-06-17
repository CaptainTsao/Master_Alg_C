/*
 * =====================================================================================
 *
 *       Filename:  frames.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年04月04日 23时39分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef FRAMES_H
#define FRAMES_H

#include "list.h"

int alloc_frame(List *frames);

int free_frame(List *frames, int frame_number);

#endif
