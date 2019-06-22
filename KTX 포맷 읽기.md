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

