# KTX 포맷 읽기



----------------------

<https://www.khronos.org/opengles/sdk/tools/KTX/file_format_spec/#1>

위 사이트의 포맷 정보 C++로 파일을 읽어 본다.



------------------------------

## 파일 구조



```
Byte[12] identifier
UInt32 endianness
UInt32 glType
UInt32 glTypeSize
UInt32 glFormat
Uint32 glInternalFormat
Uint32 glBaseInternalFormat
UInt32 pixelWidth
UInt32 pixelHeight
UInt32 pixelDepth
UInt32 numberOfArrayElements
UInt32 numberOfFaces
UInt32 numberOfMipmapLevels
UInt32 bytesOfKeyValueData
  
for each keyValuePair that fits in bytesOfKeyValueData
    UInt32   keyAndValueByteSize
    Byte     keyAndValue[keyAndValueByteSize]
    Byte     valuePadding[3 - ((keyAndValueByteSize + 3) % 4)]
end
  
for each mipmap_level in numberOfMipmapLevels1
    UInt32 imageSize; 
    for each array_element in numberOfArrayElements2
       for each face in numberOfFaces3
           for each z_slice in pixelDepth2
               for each row or row_of_blocks in pixelHeight2
                   for each pixel or block_of_pixels in pixelWidth
                       Byte data[format-specific-number-of-bytes]4
                   end
               end
           end
           Byte cubePadding[0-3]
       end
    end
    Byte mipPadding[0-3]
end
```

- 특정 데이터는 1로 바꿔야 하는 것 같다.



----------

## 파일 구조 설명

### identifier

- 파일 정보이다.

- KTX 버전 정보가 입력된다.

- 파일을 읽을때 무시하거나 identifier가 맞는지 검사를 수행하면 되겠다.
  - 틀리면 read error

```
Byte[12] FileIdentifier = {
    '«', 'K', 'T', 'X', ' ', '1', '1', '»', '\r', '\n', '\x1A', '\n'
}
```



### endianness

파일이 리틀인디언인지 빅인디언인지가 쓰여진다.

0x01020304 일 경우 리틀 인디언이다.

0x04030201 일 경우 빅인디언으로 표시된다.

0x04030201 로 표시된 경우 파일을 읽는 프로그램의 엔디안과 일치되므로 변환이 필요없다.

0x01020304 일 경우 바이트 자릿수를 스왑해줘야한다.



### glType

- 픽셀의 데이터 타입

- 압축 텍스쳐에 대한 정보는 0

|type Parameter Token Name|Corresponding GL Data Type | Special Interpretation | Floating Point|
|---|---|---|---|
|UNSIGNED_BYTE| ubyte| No| No|
|BYTE |byte |No |No|
|UNSIGNED_SHORT| ushort |No| No|
|SHORT| short| No| No|
|UNSIGNED_INT| uint| No| No|
|INT| int| No| No|
|HALF_FLOAT| half| No| Yes|
|FLOAT float| No| Yes|
|UNSIGNED_BYTE_3_3_2| ubyte| Yes| No|
|UNSIGNED_BYTE_2_3_3_REV| ubyte| Yes| No|
|UNSIGNED_SHORT_5_6_5| ushort| Yes| No|
|UNSIGNED_SHORT_5_6_5_REV| ushort| Yes| No|
|UNSIGNED_SHORT_4_4_4_4| ushort| Yes| No|
|UNSIGNED_SHORT_4_4_4_4_REV| ushort| Yes| No|
|UNSIGNED_SHORT_5_5_5_1| ushort| Yes| No|
|UNSIGNED_SHORT_1_5_5_5_REV| ushort| Yes| No|
|UNSIGNED_INT_8_8_8_8| uint| Yes| No|
|UNSIGNED_INT_8_8_8_8_REV| uint| Yes| No|
|UNSIGNED_INT_10_10_10_2| uint| Yes| No|
|UNSIGNED_INT_2_10_10_10_REV| uint| Yes| No|
|UNSIGNED_INT_24_8| uint| Yes| No|
|UNSIGNED_INT_10F_11F_11F_REV| uint| Yes| Yes|
|UNSIGNED_INT_5_9_9_9_REV| uint| Yes| Yes|
|FLOAT_32_UNSIGNED_INT_24_8_REV| n/a| Yes |No|



### glTypeSize

 이 값이 0이 아닐 경우 이 값 만큼 stride에 추가 해야한다.



### glFormat



픽셀 데이터의 포맷

| Format Name |Element Meaning and Order |Target Buffer|
|---|---|---|
|STENCIL_INDEX| Stencil Index |Stencil|
|DEPTH_COMPONENT |Depth| Depth|
|DEPTH_STENCIL |Depth and Stencil Index| Depth and Stencil|
|RED |R| Color|
|GREEN |G| Color|
|BLUE| B| Color|
|RG| R, G| Color|
|RGB| R, G, B |Color|
|RGBA |R, G, B, A |Color|
|BGR |B, G, R| Color|
|BGRA |B, G, R, A| Color|
|RED_INTEGER| iR| Color|
|GREEN_INTEGER| iG |Color|
|BLUE_INTEGER |iB |Color|
|RG_INTEGER |iR, iG| Color|
|RGB_INTEGER| iR, iG, iB |Color|
|RGBA_INTEGER |iR, iG, iB, iA |Color|
|BGR_INTEGER |iB, iG, iR |Color|
|BGRA_INTEGER| iB, iG, iR, iA |Color|



### glInternalFormat



glTexStorage2D**(**GL_TEXTURE_2D, mipmapLevel, **glInternalFormat, **pixelWidth, pixelHeight);

|Compressed Internal Format| Base Internal Format | Type | Border Type|
|---|---|---|---|
|COMPRESSED_RED| RED| Generic| unorm|
|COMPRESSED_RG| RG |Generic| unorm|
|COMPRESSED_RGB| RGB| Generic |unorm|
|COMPRESSED_RGBA| RGBA| Generic ||unorm|
|COMPRESSED_SRGB| RGB| Generic |unorm|
|COMPRESSED_SRGB_ALPHA| RGBA| Generic |unorm|
|COMPRESSED_RED_RGTC1| RED| Specific |unorm|
|COMPRESSED_SIGNED_RED_RGTC1| RED |Specific| snorm|
|COMPRESSED_RG_RGTC2| RG| Specific| unorm|
|COMPRESSED_SIGNED_RG_RGTC2| RG |Specific |snorm|
|COMPRESSED_RGBA_BPTC_UNORM| RGBA |Specific |unorm|
|COMPRESSED_SRGB_ALPHA_BPTC_-UNORM|RGBA| Specific| unorm|
|COMPRESSED_RGB_BPTC_SIGNED_-FLOAT|RGB |Specific| float|
|COMPRESSED_RGB_BPTC_UNSIGNED_-FLOAT |RGB| Specific| float|
|COMPRESSED_RGB8_ETC2| RGB| Specific| unorm|
|COMPRESSED_SRGB8_ETC2| RGB| Specific |unorm|
|COMPRESSED_RGB8_PUNCHTHROUGH_-ALPHA1_ETC2|RGB| Specific| unorm|
|COMPRESSED_SRGB8_-PUNCHTHROUGH_ALPHA1_ETC2|RGB |Specific |unorm|
|COMPRESSED_RGBA8_ETC2_EAC| RGBA| Specific| unorm|
|COMPRESSED_SRGB8_ALPHA8_ETC2_-EAC|RGBA |Specific| unorm|
|COMPRESSED_R11_EAC| RED |Specific |unorm|
|COMPRESSED_SIGNED_R11_EAC| RED| Specific |snorm|
|COMPRESSED_RG11_EAC| RG| Specific |unorm|
|COMPRESSED_SIGNED_RG11_EAC| RG| Specific |snorm|

### glBaseInternalFormat

텍스쳐 타입 기본 정보, RGB인지 RGBA인지 알아 낼 수 있다. 몇개의 채널을 사용하는지 정보를 알 수있다.

|Base Internal Format |RGBA, Depth, and Stencil Values |Internal Components|
|---|---|---|
|DEPTH_COMPONENT |Depth| D|
|DEPTH_STENCIL |Depth,Stencil |D,S|
|RED |R |R|
|RG| R,G| R,G|
|RGB| R,G,B |R,G,B|
|RGBA |R,G,B,A| R,G,B,A|
|STENCIL_INDEX| Stenci|l S|

### pixelWidth, pixelHeight, pixelDepth



pixelWidth, pixelHeight 이미지의 폭과 높이값

ex)

**glTexStorage2D**(**GL_TEXTURE_2D**, mipmapLevel, glInternalFormat, **pixelWidth, pixelHeight**);



pixelDepth는 3차원 텍스쳐일 때 사용된다.

ex)

**glTexStorage3D**(**GL_TEXTURE_3D**, mipmapLevel, glInternalFormat, pixelWidth, pixelHeight, **pixelDepth**);



### numberOfArrayElements

이미지 배열의 개수 1차원 이미지 배열 일 경우 아래와 같이 사용하면 된다.

glTexStorage2D(GL_TEXTURE_1D_ARRAY, mipmapLevel, glInternalFormat, pixelWidth, **numberOfArrayElements**);



### numberOfFaces

0 일 경우 기본 텍스쳐 큐브맵일 경우 face의 개수가 6으로 들어와야한다.

GL_TEXTURE_CUBE_MAP 설정을하면된다.



### numberOfMipmapLevels



밉맵 레벨

glTexStorage2D**(**GL_TEXTURE_2D**, mipmapLevel**, glInternalFormat, pixelWidth, pixelHeight);





### bytesOfKeyValueData



keyAndValueByteSize, keyAndValue, valuePadding 필드에 총 byte 크기



### keyAndValueByteSize



### keyAndValue



### valuePadding

파일 오프셋이 4의 배수가 되도록 해주는 padding 바이트 0~3 바이트 크기로 모두 0x00이 들어간다.



### imageSize



### cubePadding



### mipPadding



### ktx 파일 예제

```
// HEADER
0xAB, 0x4B, 0x54, 0x58, // first four bytes of Byte[12] identifier
0x20, 0x31, 0x31, 0xBB, // next four bytes of Byte[12] identifier
0x0D, 0x0A, 0x1A, 0x0A, // final four bytes of Byte[12] identifier
0x04, 0x03, 0x02, 0x01, // Byte[4] endianess (Big endian in this case)
0x00, 0x00, 0x00, 0x00, // UInt32 glType = 0
0x00, 0x00, 0x00, 0x01, // UInt32 glTypeSize = 1
0x00, 0x00, 0x00, 0x00, // UInt32 glFormat = 0
0x00, 0x00, 0x8D, 0x64, // UInt32 glInternalFormat = GL_ETC1_RGB8_OES
0x00, 0x00, 0x19, 0x07, // UInt32 glBaseInternalFormat = GL_RGB
0x00, 0x00, 0x00, 0x20, // UInt32 pixelWidth = 32
0x00, 0x00, 0x00, 0x20, // UInt32 pixelHeight = 32
0x00, 0x00, 0x00, 0x00, // UInt32 pixelDepth = 0
0x00, 0x00, 0x00, 0x00, // UInt32 numberOfArrayElements = 0
0x00, 0x00, 0x00, 0x01, // UInt32 numberOfFaces = 1
0x00, 0x00, 0x00, 0x01, // UInt32 numberOfMipmapLevels = 1
0x00, 0x00, 0x00, 0x10, // UInt32 bytesOfKeyValueData = 16
// METADATA
0x00, 0x00, 0x00, 0x0A, // UInt32 keyAndValueByteSize = 10
0x61, 0x70, 0x69, 0x00, // UTF8 key:   'api\0'
0x67, 0x6C, 0x65, 0x73, // UTF8 v: 'gles2\0'
0x32, 0x00, 0x00, 0x00, // Byte[2] valuePadding (2 bytes)
// TEXTURE DATA
0x00, 0x00, 0x02, 0x00, // UInt32 imageSize = 512 bytes
0xD8, 0xD8, 0xD8, 0xDA, // Byte[512] ETC compressed texture data...
...
```