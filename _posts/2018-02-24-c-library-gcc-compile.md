---
layout:     post
title:      "c 라이브러리 파일, gcc 컴파일"
subtitle:   "C library, GCC compile" 
date:       2018-02-24 12:00:00
categories: [development]
author:     "nicewoong"
tags:       [development, c, language, programming, c++, library]
comments: true
---

### GCC 옵션 라이브러리 관련 


* `-l` 옵션 (소문자 엘)
    * 링크할 라이브러리를 명시하는 옵션이다. 
    * 정적 라이브러리를 링크시키는데 사용되며 대상 라이브러리 파일의 이름에서 앞의 `lib`와 뒤의 `.a`를 때고 인식한다. 
    * 예를 들어 `libmylib.a` 라는 라이브러리 파일을 링크시키려면 `-lmylib` 로 옵션을 주면 된다.


<br>
* `-L` 옵션 (대문자 엘)
    * 라이브러리 위치를 정해주는 옵션이다. 
    * 사용은 다음과 같이 `-L<디렉토리명>` 으로 한다. 
    * 기본적으로 리눅스는 `/lib, /usr/lib, /usr/local/lib` 만을 검색해서 라이브러리를 찾는다. 
    * 그러므로 추가적으로 디렉토리를 검색하도록 하려면 -L 옵션을 사용하면 된다.-l 옵션 (소문자 엘)

* (출처) - http://yjaeseok.tistory.com/86



<br><br>





### c 라이브러리 파일 만들기 


#### 1.라이브러리 파일 만들기

* 리눅스 상에서 GCC컴파일러를 이용해 라이브러리를 만드려면 다음과 같은 컴파일 과정을 통해서 오브젝트 파일을 생성한다.
    

        $ gcc -c filename.c (.cpp 파일을 컴파일 할 경우 g++ -c filename.cpp)

* 컴파일이 제대로 끝났다면 확장자가 `.o`인 `filename.o`파일이 만들어 질것이다.

* 이번에는 생성된 오브젝트 파일을 이용하여 라이브러리를 만들도록 한다.
  
* 이 때 사용하는 명령어는 `ar`로 라이브러리 작성에 사용된다. 

* 아래와 같이 ar옵션 그리고 생성하고자 하는 라이브러리의 이름, 마지막으로 오브젝트 파일들의 이름을 나열한후 실행 한다. 
  (※ 윈도우에서 라이브러리 파일의 확장자는 .lib이지만 리눅스에서는 .a확장자를 지닌다.)


        $ ar crv libfile.a filename.o



#### 2. 라이브러리 파일의 사용

* 이때 라이브러리의 이름은 lib라는 말과 확장자 .a를 생략하여 사용할수 있다. 즉, libfile.a의 경우 그냥 file이라고 쓰면 된다.


        $ gcc -o executefile uselib.c -L. -l file

* 이때 만일 라이브러리 파일이 `/home/user` 디렉토리 밑에 있다면 -L 옵션을 다음과 같이 주면 된다.


        -L /home/user


* 출처: http://kukuta.tistory.com/52 [HardCore in Programming]







<br><br>

### 정적라이브러리와 동적라이브러리


#### 정적 라이브러리(또는 Archive)

* 정적라이브러리(또는 Archive)파일이라 불리우고 .a의 확장자를 가진다. 
* 여러개의 오브젝트 파일들을 하나로 묶어 사용하기 때문에 Archive파일이라고 부름 
* `컴파일 시간`에 코드를 포함하여 결정하기 때문에 정적 라이브러리라고 부른다.


        gcc -c test.c
        gcc -c app.c

* test.o 파일과 app.o 파일이 생성됨.
* test.o 파일을 Archive로 묶어 보자. 
* 라이브러리 파일의 작명법은 `lib`뒤에 이름을 붙임


        ar cr libtest.a test.o


* `libtest.a` 파일이 생성됨.
* 이 라이브러리를 사용하여 컴파일 할려면 아래와 같이 한다. 
* `-ltest`가 `libtest.a`를 지정하게 된다.
* `-L.` 은 현재 폴더 가리킴

        #gcc -o  app app.o -L. -ltest




<br>

#### 동적 라이브러리

* 실 행 시간에 라이브러리 파일을 찾아 코드를 포함하기 때문에 동적라이브러리라고 부름 
* 즉, 정적 라이브러리는 컴파일 시간에 코드를 결정하기 때문에 소스가 변경되면 새로 컴파일 해야하지만, 
* 동적 라이브러리의 경우 라이브러리만 교체하는 것으로도 변경이 가능하다. 

        gcc -c -fPIC test.c
        gcc -c app.c


* `-fPIC`옵션은 Position-Independent Code의 약자이며 `test.o`파일을 동적라이브러리로 사용하도록 컴파일 하는 옵션이다. 
* 이렇게 컴파일된 오브젝트 파일을 .so파일로 묶으면 된다.

        # gcc -shared -fPIC -o libtest.so test.o


* 컴파일은 아래와 같이 하면 된다.

        # gcc -o app app.o -L. -ltest

* 만 일 `libtest.a` 파일과 `libtest.so` 파일이 같이 있을 경우 gcc 컴파일러는 `libtest.so` 파일을 먼저 지정하게 된다. 
* 만일 libtest.a를 사용하여 컴파일 하고 싶으면 아래와 같이 실행하면 된다.


        # gcc -static -o app app.o -L. -ltest



* 출처: http://blueamor.tistory.com/707 [51%의 가능성]

