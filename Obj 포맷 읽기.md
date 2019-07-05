# Obj 포맷 모델 읽기



## 기본 정보

- 반 시계 방향으로 버텍스가 저장됨
- #은 주석
- Obj, MTL, 이미지 파일이 기본적인 구성이다.
- 소수점 6자리 까지만 지원한다..





## 파일 구조

![1561834891562](C:\Users\swkim\AppData\Roaming\Typora\typora-user-images\1561834891562.png)



### 정점 데이터

버텍스 데이터가 제공하는 좌표

- geometric vertices (v) : 기하 정점 데이터
- texture vertices (vt) : 텍스쳐 좌표 데이터
- vertex normals (vn) : 정점 노멀 데이터
- parameter space vertices (vp) : 잘 안씀



### Free-form curve/surface attributes

- 커브 속성 (잘안씀)

- 5개 타입의 기하 제공
  - basis matrix, Bezier, B-spline, Cardinal, Taylor (cstype)



### Elements



- 폴리곤 생성을 위해 엘리먼트 타입으로 다음을 지원한다.

point (p) : 점일 경우

line (l) : 선일 경우

face (f) : 삼각형, 사각형일 경우, 대부분 삼각형 데이터를 사용한다. 버텍스, 텍스쳐, 노멀 인덱스를 지원한다.

curve (curv) : 커브 데이터

2D curve (curv2) : ..

surface (surf) : ..



### Obj 파일 예제



#### 정점 데이터

4개의 버텍스 리스트 (오른손 좌표계)

ex)


```
v -5.000000 5.000000 0.000000
v -5.000000 -5.000000 0.000000
v 5.000000 -5.000000 0.000000
v 5.000000 5.000000 0.000000

vt -5.000000 5.000000 0.000000
vt -5.000000 -5.000000 0.000000
vt 5.000000 -5.000000 0.000000
vt 5.000000 5.000000 0.000000

vn 0.000000 0.000000 1.000000
vn 0.000000 0.000000 1.000000
vn 0.000000 0.000000 1.000000
vn 0.000000 0.000000 1.000000

vp 0.210000 3.590000
vp 0.000000 0.000000
vp 1.000000 0.000000
vp 0.500000 0.500000
```



#### 정점 데이터 문법 설명

- 정점 데이터
  - **v** **x y z** w (굵은 글씨는 필수 데이터)

- 버텍스의 x,y,z 좌표 커브나 표면을 요구할 경우 4번째 요소 weight를 사용한다.

  - **vp u** v w

  - u : 점, 첫번째 좌표 ,  v : 두번째 좌표  w : 기본 1.0 rational 사용

- 버텍스의 노멀
  - **vn i j k**

-  텍스쳐 버텍스 (uv 좌표)
  - **vt u v** w

 

#### Element 데이터


```
f 1/1/1 2/2/2 3/3/3
f 2/2/3 3/2/2 1/2/3
f 1/1/1 2/2/2 3/3/3
f 1/1/1 2/2/2 3/3/3
f 1/1/1 2/2/2 3/3/3
f 1/1/1 2/2/2 3/3/3
...
```

#### Element 데이터 문법 설명

- point 일 경우
  - **p v1** v2 v3 ...
- 선일 경우
  - **l** **v1**/vt1 **v2**/vt2 **v3**/vt3
- 삼각형/ 사각형일 경우
  - **f v1**/vt1 **v2**/vt2 **v3**/vt3
  -  텍스쳐 좌표, 노멀 좌표를 가질 수 있음



## 포맷 분석



### 예제 1 유타의 주전자

![1561836003074](C:\Users\swkim\AppData\Roaming\Typora\typora-user-images\1561836003074.png)

![1561836008620](C:\Users\swkim\AppData\Roaming\Typora\typora-user-images\1561836008620.png)

주전자 obj 파일

g : 그룹 이름

v : 버텍스의 좌표

vn : 버텍스 노멀

f : 버텍스 인덱싱



### 예제 2 사각형



![1561836094182](C:\Users\swkim\AppData\Roaming\Typora\typora-user-images\1561836094182.png)

![1561836146608](C:\Users\swkim\AppData\Roaming\Typora\typora-user-images\1561836146608.png)

### 예제 3 큐브

![1561836098989](C:\Users\swkim\AppData\Roaming\Typora\typora-user-images\1561836098989.png)
```
v 0.000000 2.000000 2.000000
v 0.000000 0.000000 2.000000
v 2.000000 0.000000 2.000000
v 2.000000 2.000000 2.000000
v 0.000000 2.000000 0.000000
v 0.000000 0.000000 0.000000
v 2.000000 0.000000 0.000000
v 2.000000 2.000000 0.000000

f 1 2 3 4
f 8 7 6 5
f 4 3 7 8
f 5 1 4 8
f 5 6 2 1
f 2 6 7 3
```

위 데이터를 저장하여 obj viewer로 보면 큐브 모양이 나타난다.



파일을 읽은 후 아래 형태들을 파싱해주면 끝

struct

{

​	vlist

​	vtlist

​	vnlist

​	facelist

}



텍스쳐와 Obj 파일을 연결할 필요가 있는데 MTL 파일이 이 역할을 수행한다.

