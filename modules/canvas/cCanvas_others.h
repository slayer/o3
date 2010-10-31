/*
* Copyright (C) 2010 Ajax.org BV
*
* This library is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation; either version 2 of the License, or (at your option) any later
* version.
*
* This library is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this library; if not, write to the Free Software Foundation, Inc., 51
* Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

namespace o3 
{

	struct cImage_CanvasGradient: cScr 
	{
		o3_begin_class(cScr)
		o3_end_class()

		o3_glue_gen();

		enum Types
		{
			GRADIENT_LIN,
			GRADIENT_RAD,
			__Type_Count
		};

		o3_fun void addColorStop(double offset, const Str &color)
		{
			color;
			offset;
		};

		int m_type;
		V2<double> m_CP1;
		V2<double> m_CP2;
		tVec<unsigned int> m_colorstops;
	};

	struct cImage_CanvasPattern: cScr 
	{
		o3_begin_class(cScr)
		o3_end_class()

		o3_glue_gen();
	};


	struct cImage_TextMetrics: cScr 
	{
		o3_begin_class(cScr)
		o3_end_class()
		
		o3_glue_gen();

		o3_get double width(){return mWidth;};

		double mWidth;
	};

	struct cImage_CanvasPixelArray: cScr 
	{
		o3_begin_class(cScr)
		o3_end_class()
		
		o3_glue_gen();

		tVec<unsigned char> mData;
       
		o3_fun bool __query__(int idx) 
		{       
			if (idx<0 || ((size_t)idx)>=mData.size())
				return false;
			return true;
        } 
        
        o3_fun unsigned char __getter__(iCtx* ctx, int idx, siEx* ex = 0) 
		{
            o3_unused(ctx);
            ex;
            return item(idx);
        }

        unsigned char item(int index) 
		{
            o3_trace3 trace;
			if (index<0 || ((size_t)index)>=mData.size())
				return 0;
			return mData[index];			
        }
        
        virtual o3_get int length() 
		{
            return mData.size();           
        }
	};

	struct cImage_ImageData: cScr
	{
		o3_begin_class(cScr)
		o3_end_class()
	
		o3_glue_gen();

		cImage_CanvasPixelArray mStorage;

		o3_get unsigned long width()
		{
			return 0;
		};

		o3_get unsigned long height()
		{
			return 0;
		};

//		o3_get tSi<cImage_CanvasPixelArray> data();

		o3_get siScr data()
		{
			return siScr(&mStorage);
		}
	};




	struct cImage_CanvasRenderingContext2D
	{
		// interface taken from http://www.whatwg.org/specs/web-apps/current-work/multipage/the-canvas-element.html

		void save(); // push state on state stack
		void restore(); // pop state stack and restore state

		// transformations (default transform is the identity matrix)
		void scale(double x, double y);
		void rotate(double angle);
		void translate(double x, double y);
		void transform(double a, double b, double c, double d, double e, double f);
		void setTransform(double a, double b, double c, double d, double e, double f);

		// compositing
		//attribute 
		double globalAlpha; // (default 1.0)
		//attribute 
		Str globalCompositeOperation; // (default source-over)

		// colors and styles
		//attribute 
		Str strokeStyle; // (default black)
		//attribute 
		Str fillStyle; // (default black)
		
		cImage_CanvasGradient createLinearGradient(double x0, double y0, double x1, double y1);
		cImage_CanvasGradient createRadialGradient(double x0, double y0, double r0, double x1, double y1, double r1);
		
		// these calls need communication to a dom -> 
		//CanvasPattern createPattern(HTMLImageElement image, const Str & repetition);
		//CanvasPattern createPattern(HTMLCanvasElement image, const Str & repetition);
		//CanvasPattern createPattern(HTMLVideoElement image, const Str &repetition);

		// line caps/joins
		//attribute 
		double lineWidth; // (default 1)
		//attribute 
		Str lineCap; // "butt", "round", "square" (default "butt")
		//attribute 
		Str lineJoin; // "round", "bevel", "miter" (default "miter")
		//attribute 
		double miterLimit; // (default 10)

		// shadows
		//attribute 
		double shadowOffsetX; // (default 0)
		//attribute 
		double shadowOffsetY; // (default 0)
		//attribute 
		double shadowBlur; // (default 0)
		//attribute 
		Str shadowColor; // (default transparent black)

		// rects
		void clearRect(double x, double y, double w, double h);
		void fillRect(double x, double y, double w, double h);
		void strokeRect(double x, double y, double w, double h);

		// path API
		void beginPath();
		void closePath();
		void moveTo(double x, double y);
		void lineTo(double x, double y);
		void quadraticCurveTo(double cpx, double cpy, double x, double y);
		void bezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
		void arcTo(double x1, double y1, double x2, double y2, double radius);
		void rect(double x, double y, double w, double h);
		void arc(double x, double y, double radius, double startAngle, double endAngle);
		void arc(double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise);

		void fill();
		void stroke();
		void clip();
		boolean isPointInPath(double x, double y);

		// focus management
		// needs communication with the dom
		// boolean drawFocusRing(Element element, double xCaret, double yCaret, in optional boolean canDrawCustom);

		// text
		//attribute 
		Str font; // (default 10px sans-serif)
		//attribute 
		Str textAlign; // "start", "end", "left", "right", "center" (default: "start")
		//attribute 
		Str textBaseline; // "top", "hanging", "middle", "alphabetic", "ideographic", "bottom" (default: "alphabetic")
		
		void fillText(const Str & text, double x, double y);
		void fillText(const Str & text, double x, double y, double maxWidth);
		void strokeText(const Str & text, double x, double y);
		void strokeText(const Str & text, double x, double y, double maxWidth);
		cImage_TextMetrics measureText(const Str & text);

		// drawing images
		// these calls need communication to a dom -> 
		//void drawImage(in HTMLImageElement image, double dx, double dy, in optional double dw, double dh);
		//void drawImage(in HTMLImageElement image, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh);
		//void drawImage(in HTMLCanvasElement image, double dx, double dy, in optional double dw, double dh);
		//void drawImage(in HTMLCanvasElement image, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh);
		//void drawImage(in HTMLVideoElement image, double dx, double dy, in optional double dw, double dh);
		//void drawImage(in HTMLVideoElement image, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh);

		// pixel manipulation
		cImage_ImageData createImageData(double sw, double sh);
		cImage_ImageData createImageData(cImage_ImageData *imagedata);
		cImage_ImageData getImageData(double sx, double sy, double sw, double sh);
		
		void putImageData(cImage_ImageData *imagedata, double dx, double dy);
		void putImageData(cImage_ImageData *imagedata, double dx, double dy, double dirtyX, double dirtyY, double dirtyWidth, double dirtyHeight);
	};
};