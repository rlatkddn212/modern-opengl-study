# 프리미티브 프로세싱

------------------------

## 테셀레이션

- 정점이 적은 폴리곤 메시에 디테일을 추가한다.

- 3가지 테셀레이션 파이프라인을 통해 생성된다.
  - 테셀레이션 컨트롤 쉐이더
  - 고정 함수 테셀레이션 엔진 (Tessellation primitive generation)
  - 테셀레이션 이벨류에이션 쉐이더



### 테셀레이션 컨트롤 쉐이더

- TCS 예제

```GLSL
#version 430 core                                                                 
                                                                                  
layout (vertices = 3) out;                                                        
                                                                                  
void main(void)                                                                   
{                                                                                 
    if (gl_InvocationID == 0)                                                     
    {                                                                             
        gl_TessLevelInner[0] = 5.0;                                               
        gl_TessLevelOuter[0] = 5.0;                                               
        gl_TessLevelOuter[1] = 5.0;                                               
        gl_TessLevelOuter[2] = 5.0;                                               
    }                                                                             
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     
} 
```



- layout (vertices = 3) out;

  - 출력 패치 크기 , 출력 패치에 정점들의 수이다.

  - 패치 데이터 계산에 사용되는 TCS 호출 수를 결정한다.
  - 출력 패치크기는 입력 패치 크기와 동일할 필요 없다.



- gl_in[gl_InvocationID].gl_Position;

  - 정점 쉐이더에서 TCS로 오는 모든 입력은 입력 패치의 크기에 따라 배열 안에 저장된다.

  - 각 호출마다 gl_InvocationID(호출 인덱스) 를 통해 입력 데이터에 접근할 수 있다.
  - gl_InvocationID  이외에 gl_PatchVerticesIn(정점 개수), gl_PrimitiveID(패치의 인덱스) 를 Built-in으로 제공한다.
  - vertex shader에 출력 built-in 타입 변수도 사용 할 수있다. gl_Position, gl_PointSize, gl_ClipDistance[]



- gl_TessLevelInner[0] = 5.0; gl_TessLevelOuter[0] = 5.0;
  - 테셀레이션 프리미티브 생성기에서 사용될 내부, 외부 테셀레이션 레벨을 정의한다.
  - 테셀레이션의 크기를 정의한다.
  - 정확한 의미는 패치 유형(삼각형, 사각형, 등치선 등)에 따라 다르다. 
  -  외부는 실수형 4벡터 내부는 실수형 2벡터 (삼각형의 경우 외부 3벡터, 내부 1벡터를 사용)





###  Tessellation primitive generation

- 패치를 더 작은 프리미티브로 쪼갠다.
- 사용자가 프로그래밍 할 수 없는 고정 함수이다.
-  테셀레이션의 양은 테셀레이션 내부 외부 수준에의해 정의 된다. 



### 테셀레이션 이벨류에이션 쉐이더

- TES 예제

```
#version 430 core                                                                 
                                                                                  
layout (triangles, equal_spacing, cw) in;                                         
                                                                                  
void main(void)                                                                   
{                                                                                 
    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       
                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       
                  (gl_TessCoord.z * gl_in[2].gl_Position);                        
}                                      
```



- Tessellation primitive generation 단계에서 생성된 패치에서 정점 데이터를 가져와 정점을 생성
- layout (triangles, equal_spacing, cw) in;  
  - 레이아웃 한정자
  - 패치 type, 간격, 와인딩 순서를 지정한다.
  - 패치 타입 : 등치선, 삼각형, 사각형
  - 간격 : equal_spacing, fractional_even_spacing, fractional_odd_spacing
  - 와인딩 순서 : CW, CCW
- gl_TessCoord
  - 0~1 사이로 정규화된 좌표, 삼각형의 경우 중심좌표계를 따른다.



### 프리미티브 모드

- 사각형 테셀레이션
- 삼각형 테셀레이션
- 등치선 테셀레이션



### 테셀레이션 간에 데이터 전달



테셀레이션 예제 C08_TessellationTerrain

-> 버텍스 버퍼 정점 위치지정 -> 테셀레이션 컨트롤, mvp 변환, 테셀레이션 level 지정 -> 테셀레이션 이벨류, 정점 적절히 조절, 변위맵으로 고도값 변경 -> 프래그먼트 쉐이더,  색상 지정



C08_TessellationBezierSurface

-> 



---------------

## 지오메트리 쉐이더



- 입력으로 하나의 프리미티브를 받는다.
- 출력으로 추가 프리미티브를 생성할 수 있고 출력을 제거 할 수도 있다.

- 주로 변환 피드백, 레이어 랜더링에 사용된다.



지오메트리 쉐이더 예제

```
#version 430 core                                                                 
                                                                                  
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void main()
{
	for (int i = 0; i < gl_in.length(); ++i)
    {
    	gl_Position = gl_in[i].gl_Position;
    	EmitVertex();
    }
    
    EndPrimitive();
}

```

- layout (triangles) in;
  - 레이아웃 한정자로 프리미티브 타입 입력을 지정한다.
  - 이전 단계에서 전달된 프리미티브 타입과 동일해야한다.
- layout (triangle_strip, max_vertices = 3) out;
  - 출력 레이아웃 한정자는 points, line_strip, triangle_strip 중 하나로 선택해야한다.
  - 삼각형일 경우 max_vertices는 3 선일 경우 2로 지정한다.
- 레이아웃 한정자로 인스턴스를 지정 해 줄 수 도 있다.

- gl_Position
  - 정점 쉐이더와 gl_Position를 내장 입력 변수로 사용된다.
- EmitVertex();
  - 정점을 gl_Position에 입력 후 EmitVertex를 호출하면 출력값을 저장
- EndPrimitive();
  - 프리미티브를 종료한다. 새로운 프리미티브를 시작할 수 있다.





예제 삼각형 폐기 하기 C08_GeometryShaderDiscard



예제 모델 폭파시키기 C08_GeometryShaderExplosion



예제 새로운 지오메트리 생성하기 C08_GeometryShaderMakeObj



예제 모델에 법선 출력하기 C08_GeometryShaderNormal



### 변환 피드백 활용



### 새로운 프리미티브타입



### 사각형 랜더링



C08_GeometryShaderRect

gsquads



### 레이어 랜더링

- 특정 프리미티브를 레이어드 프래임버퍼에 다른 레이어로 보낸다.
- 그림자 매핑을 할 때 유용하게 사용된다.
- 환경 맵을 랜더링하는데 유용하게 사용된다.

두가지 출력 변수를 지원한다.

```
out int gl_Layer;
out int gl_ViewportIndex;
```

gl_Layout : 멀티레이어 프레임 버퍼에서 선택된 레이어

gl_ViewportIndex : 사용할 뷰포트의 인덱스





### 여러 뷰포트 랜더링



C08_GeometryShaderViewport



