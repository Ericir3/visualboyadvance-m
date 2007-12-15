// -*- C++ -*-
// VisualBoyAdvance - Nintendo Gameboy/GameboyAdvance (TM) emulator.
// Copyright (C) 1999-2003 Forgotten
// Copyright (C) 2004 Forgotten and the VBA development team

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or(at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#pragma once

#include <memory.h>

enum DISPLAY_TYPE {
  DIRECT_DRAW = 0,
  DIRECT_3D = 1,
  OPENGL = 2
};

class IDisplay {
 public:
  IDisplay() {};
  virtual ~IDisplay() {};

  virtual bool initialize() = 0;
  virtual void cleanup() = 0;
  virtual void render() = 0;
  virtual void checkFullScreen() {};
  virtual void clear() = 0;
  virtual bool changeRenderSize(int w, int h) { return true; };
  virtual void resize(int w, int h) {};
  virtual void setOption(const char *option, int value) {};
  virtual DISPLAY_TYPE getType() = 0;
  virtual bool isSkinSupported() { return false; }
  virtual int selectFullScreenMode(GUID **) = 0;
};

inline void cpyImg32( unsigned char *dst, unsigned int dstPitch, unsigned char *src, unsigned int srcPitch, unsigned short width, unsigned short height )
{
	// fast, iterative C version
	// copies an width*height array of visible pixels from src to dst
	// srcPitch and dstPitch are the number of garbage bytes after a scanline
	register unsigned short lineSize = width<<2;

	while( height-- ) {
		memcpy( dst, src, lineSize );
		src += srcPitch;
		dst += dstPitch;
	}
}

inline void cpyImg16( unsigned char *dst, unsigned int dstPitch, unsigned char *src, unsigned int srcPitch, unsigned short width, unsigned short height )
{
	register unsigned short lineSize = width<<1;

	while( height-- ) {
		memcpy( dst, src, lineSize );
		src += srcPitch;
		dst += dstPitch;
	}
}
