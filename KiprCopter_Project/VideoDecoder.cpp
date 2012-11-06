/// VideoDecoder.cpp
#include "VideoDecoder.h"
#include "DroneConstants.h"

namespace ARDrone
{
	namespace VideoDecoder
	{
		struct RGB24BitsColor 
		{
			unsigned char red, green, blue;
		};
		
		RGB24BitsColor* RGB24OutputPixelData = NULL;
		

		int F1 = CONST_BITS - PASS1_BITS - 1;
		int F2 = CONST_BITS - PASS1_BITS;
		int F3 = CONST_BITS + PASS1_BITS + 3;
		
		short dataBlockBuffer[64]; 
		
		static short zigZagPositions[] =   
		{
		0,  1,  8, 16,  9,  2,  3, 10,
		17, 24, 32, 25, 18, 11,  4,  5,
		12, 19, 26, 33, 40, 48, 41, 34,
		27, 20, 13,  6,  7, 14, 21, 28,
		35, 42, 49, 56, 57, 50, 43, 36,
		29, 22, 15, 23, 30, 37, 44, 51,
		58, 59, 52, 45, 38, 31, 39, 46,
		53, 60, 61, 54, 47, 55, 62, 63,
		};
	
		//Cfr. Handbook of Data Compression - Page 529
		//David Salomon
		//Giovanni Motta
		
		static short quantizerValues[] = 
		{  
		3,  5,  7,  9, 11, 13, 15, 17,
		5,  7,  9, 11, 13, 15, 17, 19,
		7,  9, 11, 13, 15, 17, 19, 21,
		9, 11, 13, 15, 17, 19, 21, 23,
		11, 13, 15, 17, 19, 21, 23, 25,
		13, 15, 17, 19, 21, 23, 25, 27,
		15, 17, 19, 21, 23, 25, 27, 29,
		17, 19, 21, 23, 25, 27, 29, 31
		};
		
		static unsigned char clzlut[] = 
		{ 
		8,7,6,6,5,5,5,5, 
		4,4,4,4,4,4,4,4, 
		3,3,3,3,3,3,3,3, 
		3,3,3,3,3,3,3,3, 
		2,2,2,2,2,2,2,2, 
		2,2,2,2,2,2,2,2, 
		2,2,2,2,2,2,2,2, 
		2,2,2,2,2,2,2,2, 
		1,1,1,1,1,1,1,1, 
		1,1,1,1,1,1,1,1, 
		1,1,1,1,1,1,1,1, 
		1,1,1,1,1,1,1,1, 
		1,1,1,1,1,1,1,1, 
		1,1,1,1,1,1,1,1, 
		1,1,1,1,1,1,1,1, 
		1,1,1,1,1,1,1,1, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0, 
		0,0,0,0,0,0,0,0 
		};
		
		unsigned int StreamField;
		int StreamFieldBitIndex;
		int StreamIndex;
		
		bool PictureComplete;
		
		int PictureFormat;
		int Resolution;
		int PictureType;
		int QuantizerMode;
		int FrameIndex;
		
		int SliceCount;
		int SliceIndex;
		
		int BlockCount;
		
		int Width = -1;
		int Height = -1;
		
		int PixelRowSize;
		
		unsigned char* ImageStream;
		unsigned int ImageStreamLength = 0;
		
		std::vector<unsigned short> PixelData;
		
		struct MacroBlock
		{
			short DataBlocks[8][64]; 
		}; // MacroBlock
		
		struct ImageSlice
		{
			std::vector< ARDrone::VideoDecoder::MacroBlock > MacroBlocks;
			
			void setSize(int macroBlockCount)
			{
				MacroBlocks.resize(macroBlockCount);
			}
			
		}; //ImageSlice
		
		////////////////////////////////////////////
		ARDrone::VideoDecoder::ImageSlice ImageSlice;
		////////////////////////////////////////////
		
		
		void InverseTransform(int macroBlockIndex, int dataBlockIndex)
		{
			int workSpace[64];
			short data[64];
			
			int z1, z2, z3, z4, z5;
			int tmp0, tmp1, tmp2, tmp3;
			int tmp10, tmp11, tmp12, tmp13;
			
			int pointer = 0;
			
			for (int index = 8; index > 0; index--)
			{
				if (dataBlockBuffer[pointer + 8] == 0 &&
					dataBlockBuffer[pointer + 16] == 0 &&
					dataBlockBuffer[pointer + 24] == 0 &&
					dataBlockBuffer[pointer + 32] == 0 &&
					dataBlockBuffer[pointer + 40] == 0 &&
					dataBlockBuffer[pointer + 48] == 0 &&
					dataBlockBuffer[pointer + 56] == 0)
				{
					int dcValue = dataBlockBuffer[pointer] << PASS1_BITS;
					
					workSpace[pointer + 0] = dcValue;
					workSpace[pointer + 8] = dcValue;
					workSpace[pointer + 16] = dcValue;
					workSpace[pointer + 24] = dcValue;
					workSpace[pointer + 32] = dcValue;
					workSpace[pointer + 40] = dcValue;
					workSpace[pointer + 48] = dcValue;
					workSpace[pointer + 56] = dcValue;
					
					pointer++;
					continue;
				}
				
				z2 = dataBlockBuffer[pointer + 16];
				z3 = dataBlockBuffer[pointer + 48];
				
				z1 = (z2 + z3) * FIX_0_541196100;
				tmp2 = z1 + z3 * -FIX_1_847759065;
				tmp3 = z1 + z2 * FIX_0_765366865;
				
				z2 = dataBlockBuffer[pointer];
				z3 = dataBlockBuffer[pointer + 32];
				
				tmp0 = (z2 + z3) << CONST_BITS;
				tmp1 = (z2 - z3) << CONST_BITS;
				
				tmp10 = tmp0 + tmp3;
				tmp13 = tmp0 - tmp3;
				tmp11 = tmp1 + tmp2;
				tmp12 = tmp1 - tmp2;
				
				tmp0 = dataBlockBuffer[pointer + 56];
				tmp1 = dataBlockBuffer[pointer + 40];
				tmp2 = dataBlockBuffer[pointer + 24];
				tmp3 = dataBlockBuffer[pointer + 8];
				
				z1 = tmp0 + tmp3;
				z2 = tmp1 + tmp2;
				z3 = tmp0 + tmp2;
				z4 = tmp1 + tmp3;
				z5 = (z3 + z4) * FIX_1_175875602;
				
				tmp0 = tmp0 * FIX_0_298631336;
				tmp1 = tmp1 * FIX_2_053119869;
				tmp2 = tmp2 * FIX_3_072711026;
				tmp3 = tmp3 * FIX_1_501321110;
				z1 = z1 * -FIX_0_899976223;
				z2 = z2 * -FIX_2_562915447;
				z3 = z3 * -FIX_1_961570560;
				z4 = z4 * -FIX_0_390180644;
				
				z3 += z5;
				z4 += z5;
				
				tmp0 += z1 + z3;
				tmp1 += z2 + z4;
				tmp2 += z2 + z3;
				tmp3 += z1 + z4;
				
				workSpace[pointer + 0] = ((tmp10 + tmp3 + (1 << F1)) >> F2);
				workSpace[pointer + 56] = ((tmp10 - tmp3 + (1 << F1)) >> F2);
				workSpace[pointer + 8] = ((tmp11 + tmp2 + (1 << F1)) >> F2);
				workSpace[pointer + 48] = ((tmp11 - tmp2 + (1 << F1)) >> F2);
				workSpace[pointer + 16] = ((tmp12 + tmp1 + (1 << F1)) >> F2);
				workSpace[pointer + 40] = ((tmp12 - tmp1 + (1 << F1)) >> F2);
				workSpace[pointer + 24] = ((tmp13 + tmp0 + (1 << F1)) >> F2);
				workSpace[pointer + 32] = ((tmp13 - tmp0 + (1 << F1)) >> F2);
				
				pointer++;
			}
			
			pointer = 0;
			
			for (int index = 0; index < 8; index++)
			{
				z2 = workSpace[pointer + 2];
				z3 = workSpace[pointer + 6];
				
				z1 = (z2 + z3) * FIX_0_541196100;
				tmp2 = z1 + z3 * -FIX_1_847759065;
				tmp3 = z1 + z2 * FIX_0_765366865;
				
				tmp0 = (workSpace[pointer + 0] + workSpace[pointer + 4]) << CONST_BITS;
				tmp1 = (workSpace[pointer + 0] - workSpace[pointer + 4]) << CONST_BITS;
				
				tmp10 = tmp0 + tmp3;
				tmp13 = tmp0 - tmp3;
				tmp11 = tmp1 + tmp2;
				tmp12 = tmp1 - tmp2;
				
				tmp0 = workSpace[pointer + 7];
				tmp1 = workSpace[pointer + 5];
				tmp2 = workSpace[pointer + 3];
				tmp3 = workSpace[pointer + 1];
				
				z1 = tmp0 + tmp3;
				z2 = tmp1 + tmp2;
				z3 = tmp0 + tmp2;
				z4 = tmp1 + tmp3;
				
				z5 = (z3 + z4) * FIX_1_175875602;
				
				tmp0 = tmp0 * FIX_0_298631336;
				tmp1 = tmp1 * FIX_2_053119869;
				tmp2 = tmp2 * FIX_3_072711026;
				tmp3 = tmp3 * FIX_1_501321110;
				z1 = z1 * -FIX_0_899976223;
				z2 = z2 * -FIX_2_562915447;
				z3 = z3 * -FIX_1_961570560;
				z4 = z4 * -FIX_0_390180644;
				
				z3 += z5;
				z4 += z5;
				
				tmp0 += z1 + z3;
				tmp1 += z2 + z4;
				tmp2 += z2 + z3;
				tmp3 += z1 + z4;
				
				data[pointer + 0] = (short)((tmp10 + tmp3) >> F3);
				data[pointer + 7] = (short)((tmp10 - tmp3) >> F3);
				data[pointer + 1] = (short)((tmp11 + tmp2) >> F3);
				data[pointer + 6] = (short)((tmp11 - tmp2) >> F3);
				data[pointer + 2] = (short)((tmp12 + tmp1) >> F3);
				data[pointer + 5] = (short)((tmp12 - tmp1) >> F3);
				data[pointer + 3] = (short)((tmp13 + tmp0) >> F3);
				data[pointer + 4] = (short)((tmp13 - tmp0) >> F3);
				
				pointer += 8;
			}
			
			
			{
				short* source = data;
				short* destination = ImageSlice.MacroBlocks[macroBlockIndex].DataBlocks[dataBlockIndex];
				{
					//IntPtr sourcePtr = (IntPtr)source;
					//IntPtr destinationPtr = (IntPtr)destination;
					//CopyMemory(destinationPtr, sourcePtr, data.Length * 2);
					::memcpy(destination, source, 64 * sizeof(short));
				}
			}
			
		} // inverseTransform
		
		///////////////////////////////////////////
		int CountLeadingZeros(unsigned int value)
		{
			int accum = 0;
			
			accum += clzlut[value >> 24];
			accum += (accum == 8) ? clzlut[(value >> 16) & 0xFF] : 0;
			accum += (accum == 16) ? clzlut[(value >> 8) & 0xFF] : 0;
			accum += (accum == 24) ? clzlut[value & 0xFF] : 0;
			
			return accum;
		} //CountLeadingZeros
		
		///////////////////////////////////////////
		unsigned short MakeRgb(int r, int g, int b)
		{
			return (unsigned short)((r << 11) | (g << 5) | b);
		}
		
		///////////////////////////////////////////
		int Saturate5(int x)
		{
			if (x < 0)
			{
				x = 0;
			}
			
			x >>= 11;
			
			return (x > 0x1F) ? 0x1F : x;
		}
		
		int Saturate6(int x)
		{
			if (x < 0)
			{
				x = 0;
			}
			
			x >>= 10;
			
			return x > 0x3F ? 0x3F : x;
		}
		/////////////////////////////////////////////
		void ComposeImageSlice()
		{
			int u, ug, ub;
			int v, vg, vr;
			int r, g, b;
			
			int lumaElementIndex1 = 0;
			int lumaElementIndex2 = 0;
			int chromaOffset = 0;
			
			int dataIndex1 = 0;
			int dataIndex2 = 0;
			
			int lumaElementValue1 = 0;
			int lumaElementValue2 = 0;
			int chromaBlueValue = 0;
			int chromaRedValue = 0;
			
			int cromaQuadrantOffsets[] ={ 0, 4, 32, 36 };
			int pixelDataQuadrantOffsets[] = { 0, CONST_BlockWidth, Width * CONST_BlockWidth, (Width * CONST_BlockWidth) + CONST_BlockWidth };
			
			int imageDataOffset = (SliceIndex - 1) * Width * 16;
			
			//foreach (MacroBlock macroBlock in ImageSlice.MacroBlocks)
			for(int i = 0; i < ImageSlice.MacroBlocks.size(); i++)
			{
				ARDrone::VideoDecoder::MacroBlock macroBlock = ImageSlice.MacroBlocks.at(i);
				for (int verticalStep = 0; verticalStep < CONST_BlockWidth / 2; verticalStep++)
				{
					chromaOffset = verticalStep * CONST_BlockWidth;
					lumaElementIndex1 = verticalStep * CONST_BlockWidth * 2;
					lumaElementIndex2 = lumaElementIndex1 + CONST_BlockWidth;
					
					dataIndex1 = imageDataOffset + (2 * verticalStep * Width);
					dataIndex2 = dataIndex1 + Width;
					
					for (int horizontalStep = 0; horizontalStep < CONST_BlockWidth / 2; horizontalStep++)
					{
						for (int quadrant = 0; quadrant < 4; quadrant++)
						{
							int chromaIndex = chromaOffset + cromaQuadrantOffsets[quadrant] + horizontalStep;
							chromaBlueValue = macroBlock.DataBlocks[4][chromaIndex];
							chromaRedValue = macroBlock.DataBlocks[5][chromaIndex];
							
							u = chromaBlueValue - 128;
							ug = 88 * u;
							ub = 454 * u;
							
							v = chromaRedValue - 128;
							vg = 183 * v;
							vr = 359 * v;
							
							for (int pixel = 0; pixel < 2; pixel++)
							{
								int deltaIndex = 2 * horizontalStep + pixel;
								lumaElementValue1 = macroBlock.DataBlocks[quadrant][lumaElementIndex1 + deltaIndex] << 8;
								lumaElementValue2 = macroBlock.DataBlocks[quadrant][lumaElementIndex2 + deltaIndex] << 8;
								
								r = Saturate5(lumaElementValue1 + vr);
								g = Saturate6(lumaElementValue1 - ug - vg);
								b = Saturate5(lumaElementValue1 + ub);
								
								PixelData[dataIndex1 + pixelDataQuadrantOffsets[quadrant] + deltaIndex] = MakeRgb(r, g, b);
								
								//?????????????????????????????????//
								//RGB24OutputPixelData[dataIndex1 + pixelDataQuadrantOffsets[quadrant] + deltaIndex].red = (unsigned char)r;
								//RGB24OutputPixelData[dataIndex1 + pixelDataQuadrantOffsets[quadrant] + deltaIndex].green = (unsigned char)g;
								//RGB24OutputPixelData[dataIndex1 + pixelDataQuadrantOffsets[quadrant] + deltaIndex].blue = (unsigned char)b;
								/////////////////////////////////////
								
								r = Saturate5(lumaElementValue2 + vr);
								g = Saturate6(lumaElementValue2 - ug - vg);
								b = Saturate5(lumaElementValue2 + ub);
								
								PixelData[dataIndex2 + pixelDataQuadrantOffsets[quadrant] + deltaIndex] = MakeRgb(r, g, b);
								
								//?????????????????????????????????//
								//RGB24OutputPixelData[dataIndex2 + pixelDataQuadrantOffsets[quadrant] + deltaIndex].red = (unsigned char)r;
								//RGB24OutputPixelData[dataIndex2 + pixelDataQuadrantOffsets[quadrant] + deltaIndex].green = (unsigned char)g;
								//RGB24OutputPixelData[dataIndex2 + pixelDataQuadrantOffsets[quadrant] + deltaIndex].blue = (unsigned char)b;
								/////////////////////////////////////
							}
						}
					}
				}
				
				imageDataOffset += 16;
			}
		}
		/////////////////////////////////////////////////
		
		void AlignStreamData()
		{
			int alignedLength;
			int actualLength;
			
			actualLength = StreamFieldBitIndex;
			
			if (actualLength > 0)
			{
				alignedLength = (actualLength & ~7);
				if (alignedLength != actualLength)
				{
					alignedLength += 0x08;
					StreamField <<= (alignedLength - actualLength);
					StreamFieldBitIndex = alignedLength;
				}
			}
		}
		
		////////////////////////////////////////////////////
		int makeIntFromBytes(unsigned char* buffer, int index)
		{
			unsigned char b[4];
			b[0] = buffer[index];
			b[1] = buffer[index + 1];
			b[2] = buffer[index + 2];
			b[3] = buffer[index + 3];
			
			int Int32;
			
			/*
			 Int32 = (Int32 << 8) + b[3];
			 Int32 = (Int32 << 8) + b[2];
			 Int32 = (Int32 << 8) + b[1];
			 Int32 = (Int32 << 8) + b[0];*/
			
			
			::memcpy(&Int32, b, sizeof(int));
			return Int32;
		}
		
		////////////////////////////////////////////////////
		unsigned int PeekStreamData(unsigned char* stream, int count)
		{
			unsigned int data = 0;
			unsigned int streamField = StreamField;
			int streamFieldBitIndex = StreamFieldBitIndex;
			
			while (count > (32 - streamFieldBitIndex) && StreamIndex < (ImageStreamLength >> 2))
			{
				data = (data << (int)(32 - streamFieldBitIndex)) | (streamField >> streamFieldBitIndex);
				
				count -= 32 - streamFieldBitIndex;
				
				streamField = makeIntFromBytes(stream, StreamIndex * 4); //BitConverter.ToUInt32(stream, StreamIndex * 4);
				streamFieldBitIndex = 0;
			}
			
			if (count > 0)
			{
				data = (data << count) | (streamField >> (32 - count));
			}
			
			return data;
		}
		
		unsigned int ReadStreamData(int count)
		{
			unsigned int data = 0;
			
			
			while (count > (32 - StreamFieldBitIndex))
			{
				data = (data << (int)(32 - StreamFieldBitIndex)) | (StreamField >> StreamFieldBitIndex);
				
				count -= 32 - StreamFieldBitIndex;
				
				StreamField = makeIntFromBytes(ImageStream, StreamIndex * 4); //BitConverter.ToUInt32(ImageStream, StreamIndex * 4);
				StreamFieldBitIndex = 0;
				StreamIndex++;
			}
			
			if (count > 0)
			{
				data = (data << count) | (StreamField >> (32 - count));
				
				StreamField <<= count;
				StreamFieldBitIndex += count;
			}
			
			return data;
		}
		////////////////////////////////////////////////////////////////////
		
		void DecodeFieldBytes(int& run, int& level, bool& last)
		{
			unsigned int streamCode = 0;
			
			int streamLength = 0; ;
			int zeroCount = 0;
			int temp = 0;
			int sign = 0;
			
			//Use the RLE and Huffman dictionaries to understand this code fragment. You can find 
			//them in the developers guide on page 34.
			//The bits in the data are actually composed of two kinds of fields:
			// - run fields - this field contains information on the number of consecutive zeros.
			// - level fields - this field contains the actual non zero value which can be negative or positive.
			//First we extract the run field info and then the level field info.
			
			streamCode = PeekStreamData(ImageStream, 32);
			
			
			//Suppose we have following bit sequence:
			//00001111.....
			// 1 - Count the number of leading zeros -> 4
			//     Coarse value lookup is thus 00001
			// 2 - Lookup the additional value, for coarse value 00001 this is 3 addtional bits
			// 3 - Calculate value of run, for coarse value 00001 this is (111) + 8
			
			zeroCount = CountLeadingZeros(streamCode); // - (1)
			streamCode <<= zeroCount + 1; // - (2) -> shift left to get rid of the coarse value
			streamLength += zeroCount + 1; // - position bit pointer to keep track off how many bits to consume later on the stream.
			
			if (zeroCount > 1)
			{
				temp = (int)(streamCode >> (32 - (zeroCount - 1))); // - (2) -> shift right to determine the addtional bits (number of additional bits is zerocount - 1)
				streamCode <<= zeroCount - 1; // - shift all of the run bits out of the way so the first bit is points to the first bit of the level field.
				streamLength += zeroCount - 1;// - position bit pointer to keep track off how many bits to consume later on the stream.
				run = temp + (1 << (zeroCount - 1)); // - (3) -> calculate run value
			}
			else
			{
				run = zeroCount;
			}
			
			
			
			//Suppose we have following bit sequence:
			//000011111.....
			// 1 - Count the number of leading zeros -> 4
			//     Coarse value lookup is thus 00001
			// 2 - Lookup the additional value, for coarse value 00001 this is 4 addtional bits (last bit is sign bit)
			// 3 - Calculate value of run, for coarse value 00001 this is (xxx) + 8, multiply by sign
			
			zeroCount = CountLeadingZeros(streamCode);
			streamCode <<= zeroCount + 1; // - (1)
			streamLength += zeroCount + 1; // - position bit pointer to keep track off how many bits to consume later on the stream.
			
			if (zeroCount == 1)
			{
				//If coarse value is 01 according to the Huffman dictionary this means EOB, so there is
				//no run and level and we indicate this by setting last to true;
				run = 0;
				last = true;
			}
			else
			{
				if(zeroCount == 0)
				{
					zeroCount = 1;
					temp = 1;
				}
				
				streamLength += zeroCount;// - position bit pointer to keep track off how many bits to consume later on the stream.
				streamCode >>= (32 - zeroCount);// - (2) -> shift right to determine the addtional bits (number of additional bits is zerocount)
				//sign = (sbyte)(streamCode & 1); // determine sign, last bit is sign 
				sign = (int)(streamCode & 1); // determine sign, last bit is sign 
				
				if (zeroCount != 0)
				{
					//temp = (sbyte)(streamCode >> 1); // take into account that last bit is sign, so shift it out of the way
					//temp += (sbyte)(1 << (zeroCount - 1)); // - (3) -> calculate run value without sign
					temp = (int)(streamCode >> 1); // take into account that last bit is sign, so shift it out of the way
					temp += (int)(1 << (zeroCount - 1)); // - (3) -> calculate run value without sign
				}
				
				level = (sign == 1) ? -temp : temp; // - (3) -> calculate run value with sign
				last = false;
			}
			
			
			ReadStreamData(streamLength);
		}
		
		/////////////////////////////////////////////////////////////////
		void ClearDataBuffer()
		{
			::memset(dataBlockBuffer, 0, sizeof(short)*64);
		}
		////////////////////////////////////////////////////////////////////
		void GetBlockBytes(bool acCoefficientsAvailable)
		{
			int run = 0;
			int level = 0;
			int zigZagPosition = 0;
			int matrixPosition = 0;
			bool last = false;
			
			::memset(dataBlockBuffer, 0, 64 * sizeof(short));//Array.Clear(dataBlockBuffer, 0, dataBlockBuffer.Length);
			
			unsigned int dcCoefficient = ReadStreamData(10);
			
			if (QuantizerMode == CONST_TableQuantization)
			{
				dataBlockBuffer[0] = (short)(dcCoefficient * quantizerValues[0]);
				
				if (acCoefficientsAvailable)
				{
					DecodeFieldBytes(run, level, last);
					
					while (!last)
					{
						zigZagPosition += run + 1;
						matrixPosition = zigZagPositions[zigZagPosition];
						level *= quantizerValues[matrixPosition];
						dataBlockBuffer[matrixPosition] = (short)level;
						DecodeFieldBytes(run, level, last);
					}
				}
			}
			/*
			 else
			 {
			 //Currently not implemented.
			 //::printf("Constant quantizer mode is not yet implemented.\n");
			 }*/
		}
		
		///////////////////////////////////////////////////////////////////////////////////
		void ReadHeader()
		{
			unsigned int code = 0;
			unsigned int startCode = 0;
			
			AlignStreamData();
			
			code = ReadStreamData(22);
			
			startCode = (unsigned int)(code & ~0x1F);
			
			if (startCode == 32)
			{
				if (((code & 0x1F) == 0x1F))
				{
					PictureComplete = true;
				}
				else
				{
					if (SliceIndex++ == 0)
					{
						PictureFormat = (int)ReadStreamData(2);
						Resolution = (int)ReadStreamData(3);
						PictureType = (int)ReadStreamData(3);
						QuantizerMode = (int)ReadStreamData(5);
						FrameIndex = (int)ReadStreamData(32);
						
						switch (PictureFormat)
						{
							case kPictureFormatCIF: // (int)PictureFormats.Cif:
								Width = CONST_WidthCif << Resolution - 1;
								Height = CONST_HeightCif << Resolution - 1;
								break;
							case kPictureFormatVGA: //(int)PictureFormats.Vga:
								Width = CONST_WidthVga << Resolution - 1;
								Height = CONST_HeightVga << Resolution - 1;
								break;
						}
						
						//We assume two bytes per pixel (RGB 565)
						PixelRowSize = Width << 1;
						
						SliceCount = Height >> 4;
						BlockCount = Width >> 4;
						
						
						if(ImageSlice.MacroBlocks.size() != BlockCount)
						{
							ImageSlice.setSize(BlockCount); // = new ImageSlice(BlockCount);
							PixelData.resize(Width * Height); // = new ushort[Width * Height];
						}
						
					}
					else
					{
						QuantizerMode = (int)ReadStreamData(5);
					}
				}
			}
		}
		//////////////////////////////////////////////
		void ProcessStream()
		{
			bool blockY0HasAcComponents = false;
			bool blockY1HasAcComponents = false;
			bool blockY2HasAcComponents = false;
			bool blockY3HasAcComponents = false;
			bool blockCbHasAcComponents = false;
			bool blockCrHasAcComponents = false;
			
			//Set StreamFieldBitIndex to 32 to make sure that the first call to ReadStreamData 
			//actually consumes data from the stream
			StreamFieldBitIndex = 32;
			StreamField = 0;
			StreamIndex = 0;
			SliceIndex = 0;
			PictureComplete = false;
			
			
			while (!PictureComplete && StreamIndex < (ImageStreamLength >> 2))
			{
				ReadHeader();
				
				if (!PictureComplete)
				{
					for (int count = 0; count < BlockCount; count++)
					{
						unsigned int macroBlockEmpty = ReadStreamData(1);
						
						if (macroBlockEmpty == 0)
						{
							unsigned int acCoefficients = ReadStreamData(8);
							
							blockY0HasAcComponents = (acCoefficients >> 0 & 1) == 1;
							blockY1HasAcComponents = (acCoefficients >> 1 & 1) == 1;
							blockY2HasAcComponents = (acCoefficients >> 2 & 1) == 1;
							blockY3HasAcComponents = (acCoefficients >> 3 & 1) == 1;
							blockCbHasAcComponents = (acCoefficients >> 4 & 1) == 1;
							blockCrHasAcComponents = (acCoefficients >> 5 & 1) == 1;
							
							if ((acCoefficients >> 6 & 1) == 1)
							{
								unsigned int quantizerMode = ReadStreamData(2);
								QuantizerMode = (int)((quantizerMode < 2) ? ~quantizerMode : quantizerMode);
							}
							
							
							
							GetBlockBytes(blockY0HasAcComponents);
							InverseTransform(count, 0);
							
							
							
							GetBlockBytes(blockY1HasAcComponents);
							InverseTransform(count, 1);
							
							
							
							GetBlockBytes(blockY2HasAcComponents);
							InverseTransform(count, 2);
							
							
							
							GetBlockBytes(blockY3HasAcComponents);
							InverseTransform(count, 3);
							
							
							
							GetBlockBytes(blockCbHasAcComponents);
							InverseTransform(count, 4);
							
							
							
							GetBlockBytes(blockCrHasAcComponents);
							InverseTransform(count, 5);
							
						}
					}
					
					ComposeImageSlice();
				}
			}
		}
		////////////////////////////////////////////////
		
		
        
		bool decodeImage(unsigned char* stream, unsigned int streamLength, ARDrone::VideoDecoder::Image& resultImage)
		{
			Width = Height = -1;
			ImageStream = stream;
			ImageStreamLength = streamLength;
			ProcessStream();
			resultImage.width = Width;
			resultImage.height = Height;
			
			if(-1 != Width && -1 != Height)
			{
				unsigned short red_mask = 0xF800;
				unsigned short green_mask = 0x7E0;
				unsigned short blue_mask = 0x1F;
				
				int length = Width * Height;
				for(int i = 0, j = 0; i < length; i++, j+=3)
				{
					//unsigned short w = PixelData[i];
					unsigned char red = (PixelData[i] & red_mask) >> 11;
					unsigned char green = (PixelData[i] & green_mask) >> 5;
					unsigned char blue = (PixelData[i] & blue_mask);
					resultImage.data[j] = red << 3;
					resultImage.data[j+1] = green << 2;
					//Bad Access Exception here
					resultImage.data[j+2] = blue << 3;
				}  
				return true;
			}
			else 
			{
				::printf("image decoding FAIL!!");
				return false;
			}
		}
	}// namespace VideoDecoder
}//namespace ARDrone
