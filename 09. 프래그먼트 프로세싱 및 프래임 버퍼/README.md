# 프래그먼트 프로세싱 및 프래임버퍼

-------------

## 프래그먼트 쉐이더

- 레스터라이제이션에 의해 생성된 프래그먼트를 처리한다.
- 윈도우 공간에 좌표를 가진다.
- 마지막 정점처리 단계에서 얻어진 정점들이 보간된 값을 가진다.
- 깊이, 스텐실, 색상 값을 출력으로 얻을 수 있다.



폐기 명령에 엑세스 할 수 있다.

프래그먼트의 출력값이 삭제된다.

- fragment 테스트 단계를 프레그먼트 쉐이더 이전에 실행 할 수 있다.

```
layout(early_fragment_tests) in;
```

- 이 옵션을 적용한 후 gl_FragDepth에 쓰는걸 시도하면 기록된 값을 무시된다.



### 빌트인 입력 변수

```
in vec4 gl_FragCoord;
in bool gl_FrontFacing;
in vec2 gl_PointCoord;

in int gl_SampleID;
in vec2 gl_SamplePosition;
in int gl_SampleMaskIn[];

in float gl_ClipDistance[];
in int gl_PrimitiveID;

// 지오메트리 쉐이더에서 레이어를 나눈 경우 사용됨
in int gl_Layer;
in int gl_ViewportIndex;
```

- gl_FragCoord

  - 윈도우 좌표계에서 프래그먼트의 위치값이다. x,y,z 값인데 x,y는 윈도우 좌표고 gl_FragDepth값을 사용하지 않으면 z값이 깊이 버퍼에 기록된다. w값은 마지막 정점 처리단계에서 gl_Position값에 대한 1/클립좌표계 이다.

  - layout(origin_upper_left) in vec4 gl_FragCoord; 를 추가하면 원점 좌표를 지정해 줄 수 있다.
- gl_FrontFacing
  - face가 정면일 경우 ture, 후면일 경우 false 값을 가진다.
- gl_PointCoord
  - 프리미티브 내에서 0~1 범위에 점의 좌표
- gl_SampleID
  - 샘플 식별자
- gl_SamplePosition
  - 프래그먼트에 샘플 위치 0~1에 범위 값을 가짐
- gl_SampleMaskIn
  - 샘플 마스크에 대한 비트 필드
- gl_ClipDistance
  - 보간된 클립 평면
- gl_PrimitiveID
  - 프리미티브 식별자

### 출력 변수

```
out float gl_FragDepth;
```

 깊이를 출력할 수 있다.



### 보간 지시어(Interpolation qualifiers)

- flat
  - 보간 처리하지 않는다.

- noperspective
  - 선형적으로 보간된다.

- smooth
  - 원근법으로 올바르게 보간된다.



원근 보간 선형 보간 예제 C09_Interpolation



---------------------

## 프래그먼트 별 테스트



### 시저 테스트

특정 사각형안에 들어오지 않은 프래그먼트를 제거한다.

`glScissor(GLint x, GLint y, GLsizei width, GLsizei height);`



### 스텐실 테스트

- 스텐실 테스트를 하려면 스텐실 버퍼가 필요하다.
- 스텐실 버퍼는 이미지 형식의 버퍼이다.



### 깊이(z) 테스트

- 프래그먼트의 깊이 값을 테스트한다.
- 깊이 테스트를 통과하면 깊이 버퍼에 새로운 값이 업력되고 통과하지 못하면 프래그먼트에서 폐기됨



테스트 예제 C09_PerFragmentTest



-------------

## 색상 출력



## 블랜딩

- 프래그먼트의 색상을 색상 버퍼의 색상과 혼합하여 새로운 색을 만들어냄

- 이미지를 투명하게 해줄 수 있다.



블랜딩 예제 C09_Blending



### 논리 연산

- 색상을 나타내는 비트 패턴에서 수행되는 부울 연산이다.

- GL_COLOR_LOGIC_OP를 사용하여 활성화 할 수 있다.
- 논리 연산을 활성화하면 blend이 비활성화 된다.



### 색상 마스크

- 

----------------

## 오프스크린 랜더링



### 프레임 버퍼 생성

- 컬러버퍼, 스텐실버퍼, 깊이버퍼는 프래임 버퍼에 저장된다.
- 사용자가 정의하여 프레임 버퍼를 생성할 수 있다.
- glGenFramebuffers : 프레임 버퍼 생성
- glBindFramebuffer : 프레임 버퍼를 바인딩



예제 C09_FrameBuffer



### 어테치먼트

예제 C09_FrameBufferAttechment







### 레이어 프레임 버퍼



예제 C09_LayerFrameBuffer



### 프레임 버퍼 완전성

- 프레임 버퍼 객체가 제대로 설정되어 있는지 확인해야한다.
- 어태치먼트 완전성 : 최소 하나의 색상 첨부
- 프레임 버퍼 완전성 : 최소 하나의 buffer를 첨부
- 프레임 버퍼 확인 : 버퍼 메모리할당
- 프레임 버퍼 읽기 : 



### 스트레오 랜더링



예제 C09_StereoRendering



------------

## 안티에일리어싱

### 필터링 효과

예제 C09_Filtering



### 멀티 샘플링

예제 C09_MultiSampling



### 멀티 샘플 텍스쳐



### 샘플별 쉐이딩 활성화



### 중심 샘플링



----------

## 고급 프레임 버퍼 포맷



### 어테지먼트 없이 랜더링



### 부동소수점 프레임버퍼



### HDR(high dynamic range)



### 톤 매핑



HDR 예제  C09_HDR



### 블룸 효과



### 정수형 프레임 버퍼



### SRGB



-----------

## 포인트 스프라이트



### 점에 텍스쳐 입히기



예제 우주 랜더링 C09_Universe



### 점인자



### 모양있는 점



### 점 회전하기



---------------

## 이미지 얻어오기



### 프레임 버퍼 읽기



### 스크린샷



### 프레임 버퍼간 데이터 복사하기



