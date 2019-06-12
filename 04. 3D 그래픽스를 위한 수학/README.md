3D 그래픽스를 위한 수학

참고한 책에서는 자체 lib을 사용하지만 여기서는 glm을 이용하여 3D 그래픽스 수학을 배워보자.

수학적인 내용은 이 문서를 보는 것보다 강의를 듣거나 다른 수학 문서를 참고 하는게 좋다.



-------------------------------------

### 3D 그래픽스 수학

#### 1. 벡터

- 벡터 란 무엇인가?
  - 크기와 방향을 나타낼 수 있다.
  - 벡터를 사용하여 점을 표현 할 수도 있다.
  
- 벡터의 내적
  - 라이팅 모델에 사용된다. (diffuse 라이팅)
  - 두 벡터 사이의 각도를 구할 수 있다.
  - 내적의 결과는 스칼라이다.
  - 내적 공식은 다음과 같다.
   ![{\displaystyle \mathbf {\color {red}a} \cdot \mathbf {\color {blue}b} =\sum _{i=1}^{n}{\color {red}a}_{i}{\color {blue}b}_{i}={\color {red}a}_{1}{\color {blue}b}_{1}+{\color {red}a}_{2}{\color {blue}b}_{2}+\cdots +{\color {red}a}_{n}{\color {blue}b}_{n}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/5bd0b488ad92250b4e7c2f8ac92f700f8aefddd5)
    ![{\displaystyle \mathbf {a} \cdot \mathbf {b} =\|\mathbf {a} \|\ \|\mathbf {b} \|\cos(\theta ),}](https://wikimedia.org/api/rest_v1/media/math/render/svg/f578afaa0ed0f3728d4a6546d11b95456ec84647)
  
- 벡터의 외적
  - 외적의 결과는 벡터이다.
  - 외적 계산에서 나오는 스칼라 값도 자주 활용된다.
  - 외적의 경우 계산되는 벡터의 순서도 중요하다.
  - 외적 공식은 다음과 같다.
  ![\mathbf {a} =\mathbf {b} \times \mathbf {c} ](https://wikimedia.org/api/rest_v1/media/math/render/svg/8e4d134fa6d725f5648e6dd39fb112a22a09d11f)
  ![{\displaystyle \mathbf {a} ={\begin{bmatrix}a_{x}\\a_{y}\\a_{z}\end{bmatrix}},\mathbf {b} ={\begin{bmatrix}b_{x}\\b_{y}\\b_{z}\end{bmatrix}},\mathbf {c} ={\begin{bmatrix}c_{x}\\c_{y}\\c_{z}\end{bmatrix}}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/5664cca9afe2b7bcd3c5449c038f6257128b730f)
      ![{\displaystyle a_{x}=b_{y}c_{z}-b_{z}c_{y}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/d37e6a72deeb92305976e28978611cc764efd2bd)
      ![{\displaystyle a_{y}=b_{z}c_{x}-b_{x}c_{z}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/c71d9a7826acac7affc19e813f6a8744a7d227b3) 
      ![{\displaystyle a_{z}=b_{x}c_{y}-b_{y}c_{x}.}](https://wikimedia.org/api/rest_v1/media/math/render/svg/df01e0774c7c3da6b1421f2d05d9041f7bd9e547) 
  - 아래와 같은 공식으로 계산될 수 있다.
      ![{\displaystyle \mathbf {a} \times \mathbf {b} =\left\|\mathbf {a} \right\|\left\|\mathbf {b} \right\|\sin(\theta )\ \mathbf {n} }](https://wikimedia.org/api/rest_v1/media/math/render/svg/d48c9d8c853551482314bd603df694e0fd4c995f)
  - sin 값을 통해 CCW인지 CW인지 체크 가능하다.
  - 외적으로 구해진 벡터의 기하학적 의미는 3차원에서 계산에 사용한 두 벡터에 수직인 벡터이다.
  
- 벡터의 길이
  
  - 피타고라스 정리로 구할 수 있다.
  
- 반사와 굴절
  - reflection
[![img](https://upload.wikimedia.org/wikipedia/commons/thumb/e/ef/Mount_Hood_reflected_in_Mirror_Lake%2C_Oregon.jpg/220px-Mount_Hood_reflected_in_Mirror_Lake%2C_Oregon.jpg)](https://en.wikipedia.org/wiki/File:Mount_Hood_reflected_in_Mirror_Lake,_Oregon.jpg)
  - 반사의 경우 빛의 입사각과 반사각이 같다.
- ![1560307901092](C:\Users\swkim\AppData\Roaming\Typora\typora-user-images\1560307901092.png)
  
  - 위 그림처럼 입사 벡터를 a,b 벡터로 분해 할 수 있다.
  - 반사벡터의 경우 a벡터에는 영향을 주지 않고 b 벡터의 방향만 바뀐다는 것을 알 수 있다.
  - 그래서 공식은 아래와 같다.
  - R(reflect) = R(in) - 2(dot(N, R(in))N
  
  - refraction
  ![img](https://upload.wikimedia.org/wikipedia/commons/thumb/8/85/Refraction_photo.png/220px-Refraction_photo.png)
  - 굴절은 굴절률(n)이라는 단위가 추가된다. 
  - 공기(굴절률 1)중에서 매질(굴절률 k)로 이동할 경우
  - 공기에서 매질로 굴절될 경우, 매질 굴절률 /공기 굴절률 = sin(입사각)/ sin(굴절각)
  - ![img](https://www.scratchapixel.com/images/upload/shading-intro/shad-refraction6.png?)
  - 공식은 책에 딸랑 식만 적어뒀는데, 다른 사이트를 찾아보는 것이 좋겠다.
  - 참고 사이트 : <https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel>



#### 2. 행렬

- 행렬이란 무엇인가?
  - 단순한 숫자의 배열이다. 행렬 연산을 잘 활용하면 연산을 빠르게 하는 장치가 될 수 있다.
- 행렬의 연산
  - 행렬 연산은 그렇게 어렵지 않으니 책을 참고하자.

------------------------------------

### 변환

- OpenGL 의 좌표 공간
  - 모델 공간 : 그래픽 툴로 만들어진 모델의 좌표 공간이다.
  - 월드 공간 : 모델 공간에서 이동, 크기, 회전등으로 변환된 좌표 공간
  - 뷰 공간 : 월드 공간에서 카메라로 봤을 때의 좌표 공간
  - 클립 공간 : 클리핑을 수행하는 공간
  - NDC 공간 : 원근 변환이 이루어진 좌표 공간
  - 원도우 공간 : 픽셀 좌표 공간



- 좌표 변환

  - 단위 행렬
  - ![I_{1}={\begin{bmatrix}1\end{bmatrix}},\ I_{2}={\begin{bmatrix}1&0\\0&1\end{bmatrix}},\ I_{3}={\begin{bmatrix}1&0&0\\0&1&0\\0&0&1\end{bmatrix}},\ \cdots ,\ I_{n}={\begin{bmatrix}1&0&0&\cdots &0\\0&1&0&\cdots &0\\0&0&1&\cdots &0\\\vdots &\vdots &\vdots &\ddots &\vdots \\0&0&0&\cdots &1\end{bmatrix}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/e1a4218ab6975ad1809415aa168ab6371b91bafc)
  - 이동 행렬
  - ![ T_{\mathbf{v}} =  \begin{bmatrix} 1 & 0 & 0 & v_x \\ 0 & 1 & 0 & v_y \\ 0 & 0 & 1 & v_z \\ 0 & 0 & 0 & 1 \end{bmatrix} ](https://wikimedia.org/api/rest_v1/media/math/render/svg/f8291f8c9e148126f931b49fa4fa9a96827aceeb)
  - 회전 행렬
  - ![{\displaystyle {\begin{alignedat}{1}R_{x}(\theta )&={\begin{bmatrix}1&0&0\\0&\cos \theta &-\sin \theta \\[3pt]0&\sin \theta &\cos \theta \\[3pt]\end{bmatrix}}\\[6pt]R_{y}(\theta )&={\begin{bmatrix}\cos \theta &0&\sin \theta \\[3pt]0&1&0\\[3pt]-\sin \theta &0&\cos \theta \\\end{bmatrix}}\\[6pt]R_{z}(\theta )&={\begin{bmatrix}\cos \theta &-\sin \theta &0\\[3pt]\sin \theta &\cos \theta &0\\[3pt]0&0&1\\\end{bmatrix}}\end{alignedat}}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/a6821937d5031de282a190f75312353c970aa2df)
  - 오일러 각
  - 스케일 행렬
  - ![S_{v}={\begin{bmatrix}v_{x}&0&0\\0&v_{y}&0\\0&0&v_{z}\\\end{bmatrix}}.](https://wikimedia.org/api/rest_v1/media/math/render/svg/4d4561ec79e4ad2fb898cf7b2f4ec0873a01fb31)
- 변환 연결
- 쿼터니언
- 모델 뷰 변환
  - 월드 공간 변환이 끝난 뒤 카메라가 보는 위치로 변환
- lookat 행렬
  - 원점을 카메라의 중심으로 이동하게 하는 변환 행렬
- 프로젝션 변환
  - 원근 행렬
  - 정사영

-----------------------------------------

### 선, 곡선, 스플라인 보간

- 보간

  - 점 A, 점 B 사이에 선분 위에 있는 점의 위치를 보간을 통해 구할 수 있다.
  - P = (1 - t)A + tB   ------------- (0<= t <=1)

- 곡선
  
  - 두 점 사이에 곡선을 나타내기 위해선 제어 점이 필요하다.
  - 각 제어점을 보간하면 간단하게 곡선이 만들어진다.
  - 제어점 A, B, C (A,C는 종단점) 가 있을 경우 곡선 위의 점 P를 구하면
  
    - D = A + t(B - A)
  - E = B + t(C - B)
    - P = D + t(E - D)
  - 정리하면 다음과 같은 2차 방정식을 구할 수 있다.
    - P = A + 2t(B-A) + t^2(C - 2B + A)
  - 이 표현식이 2차 베지어 곡선(quadratic bezier)이다.
    - [![Construction of a quadratic Bézier curve](https://upload.wikimedia.org/wikipedia/commons/thumb/6/6b/B%C3%A9zier_2_big.svg/240px-B%C3%A9zier_2_big.svg.png)](https://en.wikipedia.org/wiki/File:Bézier_2_big.svg)
  - 3차 베지어 곡선
  - 3차 베지어 곡선의 경우 4개의 제어점을 가진다.(2개는 종단점)
    - 위와 마찬가지 방식으로 공식을 유도 할 수 있다.
    - 이를 3차베지어(cubic_bezier)
    - [![Construction of a cubic Bézier curve](https://upload.wikimedia.org/wikipedia/commons/thumb/8/89/B%C3%A9zier_3_big.svg/240px-B%C3%A9zier_3_big.svg.png)](https://en.wikipedia.org/wiki/File:Bézier_3_big.svg)
  
- 스플라인
  
  - 스플라인은 여러 곡선으로 이루어진 긴 곡선
  
  - 3차 베지어 스플라인 - B-spline
    - 3차 베지어 곡선으로 이루어진 스플라인



