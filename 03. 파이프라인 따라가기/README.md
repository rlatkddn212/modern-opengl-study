## 파이프라인 따라가기

- OpenGL 파이프라인을 시작 부터 끝까지 두루 살펴본다.
- 고정 함수 블록(Test, 레스터라이즈 등), 프로그래밍 가능한 블록(쉐이더 스테이지)

![Rendering Pipeline Flowchart](https://www.khronos.org/opengl/wiki_opengl/images/RenderingPipeline.png)

- 위 그림과 같은 순서의 파이프라인으로 동작한다. 이번장에서 이 모든 것을 다룬다.

  1) 버텍스 쉐이더에 데이터 전달

  2) 테셀레이션

  3) 지오메트리 쉐이더

  4) vertex Post-Processing

  5) 프리미티브 어셈블리

  6) 래스터라이제이션

  7) 프래그먼트 쉐이더

  8) Per-Sample Operations (멀티 샘플링 관련, 이번장은 다루지 않는 듯)

- 기타 (프레임버퍼 동작, 컴퓨트 쉐이더) 를 다룬다.



### 버텍스 쉐이더에 데이터 전달하기



- 버텍스 쉐이더 수행 전 버텍스 페칭, 버텍스 풀링이 실행되어 vertex shader에 입력을 제공해준다.

- 버텍스 쉐이더
  - 버텍스 쉐이더는 필수 스테이지다.
  - 버텍스(정점) 변환을 한다. (주로 이동, 회전, 카메라, 월드 행렬 변환들이 수행된다.)
- 버텍스 쉐이더는 **in, out 저장 지시어**를 사용하여 저장하거나 다른 쉐이더로 보낼 수 있다.
  - in의 경우 입력, out의 경우 출력이다.

<간단한 vertex Shader 프로그램>

![1559882572144](C:\Users\swkim\AppData\Roaming\Typora\typora-user-images\1559882572144.png)

- in 저장 지시어의 경우 cpp 코드에서 glVertexAttrib**() 함수를 통해 입력 가능하다.

- 다른 쉐이더 스테이지 간에도 in /out 지시어를 사용하여 데이터를 보낼 수 있다.
  - out 지시어를 사용하면 gl_Position 과 동일한 방법으로 처리된다.

- 인터페이스 블록으로 그룹화하여 데이터를 전달할 수도 있다.

- 버텍스 속성 갱신, 스테이지간 데이터 전달 예제는 C03_DataTransfer에서 확인 가능하다.




(인터 페이스 블록은 책을 보거나 인터넷에서 찾아보고, C03_DataTransfer에 Image.glsl, vertex.glsl 을 수정하여 테스트 해보자.)



### [함수]

- glVertexAttrib**

  - 설명 : vertex의 속성 값(정점, 텍스쳐 좌표 등)을 vertex 쉐이더에 전달하는 함수, 매 프레임마다 갱신 가능하다.

  - GLuint index : layout 지시어와 위치를 동일하게 지정해야한다. layout(location = 2) 일 경우 index도 2
  - const GLfloat* v : 데이터 값



### 테셀레이션

- 버텍스 쉐이더가 처리된 후 쉐이더를 사용하여 적용할 수 있다.
- 테셀레이션은 프리미티브를 여러 개의 작은 프리미티브로 분할 하는 작업을 한다.
- 테셀레이션 컨트롤 쉐이더, 고정 함수 테셀레이션 엔진, 테셀레이션 이벨류에이션 쉐이더로 구성된다.



**테셀레이션 컨트롤 쉐이더** 

- 첫번째 테셀레이션 단계이다.

- 2가지 역할을 수행

  1) 얼마나 분할 할 껀지 결정한다. 테셀레이션 엔진에 보낼 테셀레이션의 레벨을 설정하면된다. 

  2) 테셀레이션이 수행된 다음에 실행되는 테셀레이션 이벨류에이션에 보낼 데이터를 생성한다.

- 패치를 점, 선, 삼각형으로 분할 한다.
  - 패치는 점, 선, 삼각형이 분할되기 전 프리미티브를 말한다.
- 패치당 정점의 개수를 glPatchParameteri 함수로 조정할 수 있다.
- glPatchParameteri 에 대응하는 쉐이더 layout 지시어는 layout(vertices=N) out;
- 내장 출력 변수를 통해 테셀레이션 인자를 저장할 수 있다.
  - gl_TessLevelInner :
  - gl_TessLevelOuter : 
- 사용자 지정 출력 변수
  - gl_in, gl_out, gl_InvocationID



### [함수]

- glPatchParameteri
  - 설명 : 패치당 제어점 개수 조절
  - GLenum pname
  - GLint value





테셀레이션 = 패치

glpatchParameteri를 사용하여 제어점 개수로 하여 호출



**테셀레이션 엔진**

- 작은 프리미티브로 분할시킨다.
- 분할된 프리미티브는 테셀레이션 이벨류에이션 쉐이더로 전달된다.



**테셀레이션 이벨류에이션 쉐이더**

- 테셀레이션 엔진에 의해 생성된 각 버텍스에 대해 한번씩 호출 수행
- 내장 변수를 사용하여 정점 위치를 계산한다. 
  - gl_TessCoord : 무게 중심 좌표
  - gl_in [] : 테셀레이션 컨트롤 쉐이더에서 저장한 gl_out과 대응된다.



C03_Tessellation 예제에서 실행 해볼 수 있다.

![1559933284197](C:\Users\swkim\AppData\Roaming\Typora\typora-user-images\1559933284197.png)



### [함수]

- glPolygonMode
  - 설명 : wire frame 느낌으로 출력할 수 있다.
  - GLenum face : rendering할 폴리곤의 face 방향이 어느 쪽을 향하지(화면 앞, 뒤)
  - GLenum mode : 폴리곤을 어떻게 그릴지, GL_LINE으로 설정시 와이어 프레임과 동일





### 지오메트리 쉐이더

- 테셀레이션과 래스터라이저 사이에서 수행되는 쉐이더이다.
- 데이터 흐름의 양을 증가시키거나 감소 시킬 수 있다.
  - 래스터라이저로 보내지는 vertex들을 생성할 수 있다.
- 삼각형을 점으로 만들거나 여러 점을 삼각형으로 만들 수도 있다.
- EmitVertex를 호출하여 지오 메트리 셰이더에 정점을 생성 할 수 있다.
- EndPrimitive를 호출하여 프리미티브를 생성 할 수 있다.
  - 예제에서는 점을 생성하므로 EndPrimitive를 호출할 필요는 없다.(함수 종료시 호출된다.)



C03_Tessellation 에서 아래 코드에 주석을 풀어 테스트 해보자.

shaderCodies.push_back(make_pair(ReadShaderFile("gs.glsl"), GL_GEOMETRY_SHADER));



### 클리핑, 프리미티브 어셈블리, 래스터라이제이션



**프리미티브 어셈블리**

- 삼각형, 선 과 같이 vertex를 연결하는 작업을 한다.



**vertex Post-Processing**

- 클리핑과 뷰포트 변환을 실행한다.
- 컬링을 통해 후면 방향의 삼각형을 제거한다.



**래스터라이제이션**

- 삼각형을 화면 좌표로 이동 시키는 작업을 한다.
- 자세한 알고리즘은 <https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage> 사이트를 참고해보자.



### 프래그먼트 쉐이더

- 마지막으로 프로그래밍 할 수 있는 쉐이더이다.
- 한 픽셀(프래그먼트)을 입력 받아 픽셀의 색상을 지정하는 쉐이더이다.
- 정점 입력 값을 보간하여 픽셀이 지정된다. (아마도 보간되는 예제를 많이 봤을 것 같다.) 



### 프레임버퍼 동작

- 그래픽 파이프라인의 마지막 단계이다.
- 화면에 보이는 영역이 버퍼에 저장된다.



### 컴퓨트 쉐이더

- 그래픽스 파이프라인과 관련없이 별개로 동작하는 쉐이더

