// Copyright 2006 Google Inc. All Rights Reserved.
// Author: agl@imperialviolet.org (Adam Langley)
//
// Copyright (C) 2006 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef JBIG2ENC_JBIG2STRUCTS_H__
#define JBIG2ENC_JBIG2STRUCTS_H__

enum {
  segment_symbol_table = 0,
  segment_imm_generic_region = 38,
  segment_page_information = 48,
  segment_imm_text_region =  6,
  segment_end_of_page = 49,
  segment_end_of_file = 51
};

// note that the < 1 byte fields are packed from the LSB upwards.
struct jbig2_segment {
  u32 number;
  unsigned type : 6;
  unsigned page_assoc_size : 1;
  unsigned deferred_non_retain : 1;
  unsigned retain_bits : 5;
  unsigned segment_count : 3;
  u8 page;
  u32 len;
} __attribute__((packed));

struct jbig2_segment_referring {
  u32 number;
  unsigned type : 6;
  unsigned page_assoc_size : 1;
  unsigned deferred_non_retain : 1;
  unsigned retain_bits : 5;
  unsigned segment_count : 3;
  u8 referred_segment;
  u8 page;
  u32 len;
} __attribute__((packed));

#define JBIG2_FILE_MAGIC "\x97\x4a\x42\x32\x0d\x0a\x1a\x0a"

struct jbig2_file_header {
  u8 id[8];
  u8 organisation_type : 1;
  u8 unknown_n_pages : 1;
  u8 reserved : 6;
  u32 n_pages;
} __attribute__((packed));

struct jbig2_page_info {
  u32 width;
  u32 height;
  u32 xres;
  u32 yres;
  u8 is_lossless : 1;
  u8 contains_refinements : 1;
  u8 default_pixel : 1;
  u8 default_operator : 2;
  u8 aux_buffers : 1;
  u8 operator_override : 1;
  u8 reserved : 1;
  u16 segment_flags;
} __attribute__((packed));

struct jbig2_generic_region {
  u32 width;
  u32 height;
  u32 x;
  u32 y;
  u8 comb_operator;
  
  u8 mmr : 1;
  u8 gbtemplate : 2;
  u8 tpgdon : 1;
  u8 reserved : 4;

  // generic region segment here. You may not need to write all 8 bytes here.
  // If the template is 1..3 only the first two are needed.
  signed char a1x, a1y, a2x, a2y, a3x, a3y, a4x, a4y;
} __attribute__ ((packed));

struct jbig2_symbol_dict {
  u8 sdhuff:1;
  u8 sdrefagg:1;
  u8 sdhuffdh:2;
  u8 sdhuffdw:2;
  u8 sdhuffbmsize:1;
  u8 sdhuffagginst:1;
  u8 bmcontext:1;
  u8 bmcontextretained:1;
  u8 sdtemplate:2;
  u8 sdrtemplate:1;
  u8 reserved:3;

  signed char a1x, a1y, a2x, a2y, a3x, a3y, a4x, a4y;
  
  // refinement AT flags omitted

  u32 exsyms;
  u32 newsyms;
} __attribute__((packed));

struct jbig2_text_region {
  u32 width;
  u32 height;
  u32 x;
  u32 y;
  u8 comb_operator;
  
  // fixme: this two byte field is packed backwards by GCC ;(
  u8 sbcombop2:1;
  u8 sbdefpixel:1;
  u8 sbdsoffset:5;
  u8 sbrtemplate:1;
  u8 sbhuff:1;
  u8 sbrefine:1;
  u8 logsbstrips:2;
  u8 refcorner:2;
  u8 transposed:1;
  u8 sbcombop1:1;
 
  // huffman flags omitted
  // at flags omitted
  u32 sbnuminstances;
  // huffman decoding table omitted
} __attribute__((packed));



#endif  // JBIG2ENC_JBIG2STRUCTS_H__
