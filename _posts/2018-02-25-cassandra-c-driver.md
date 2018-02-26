---
layout:     post
title:      "Cassandra(카산드라) C 드라이버 설치"
subtitle:   "Cassandra C Driver install" 
date:       2018-02-24 12:00:00
categories: [development]
author:     "nicewoong"
tags:       [development, linux, c, language, programming, c++, library, cassandra]
comments: true
---


### 직접 빌드 하는 것 말고, 바이너리 패키지 다운로드 받아보기


(2018-02-26)


* 위에서는 깃허브에서 클론한 프로젝트를 직접 빌드하는 과정을 거쳤다. 
* 아무것도 모르고 해서 `make`, `c library` 사용 및 빌드하는 과정이 너무 생소했다. 그래서 멘붕이었다. 
* gcc 컴파일 옵션, make, c library 에 대해 대략적으로 어제 다시 공부하긴 했다. 
* 그래서 다시 빌드하면 이제 잘 할 수 있을 거 같다. 
* 그리고 공부한 덕분에 교수님께서 작성해놓으신 프로젝트 `makefile` 을 건드려야 할 때가 분명 올텐데, 
  그 때 잘 할 수 있을 것 같다.대강 이해가 된다 이제. 


* 그럼 직접 패키지를 다운받아서 c driver 를 사용해보도록 하자. 

<br>
* (참고 링크)
  * [공식 설명 문서(v2.8) - DataStax C/C++ Driver for Apache Cassandra](https://docs.datastax.com/en/developer/cpp-driver/2.8/topics/)
  * [cpp-drivere 우분투 v2.8 다운로드 서버](http://downloads.datastax.com/cpp-driver/ubuntu/16.04/cassandra/v2.8.1/)
  * [cpp-driver 우분투 디펜던시 다운로드 서버(최신거)](http://downloads.datastax.com/cpp-driver/ubuntu/16.04/dependencies/)  


* 위 서버로 접속하면 cpp-driver 도 그렇고, dependancies 도 그렇고 모두 .deb 파일이 올라가 있다. 

* 그럼 이걸 어쩌란 말인가? 

* 그리고 디펜던시는 도대체 뭐 어쩌라고 올려두는건가? 

* 디펜던시도 다운받아야 하는건가? 그럼 그걸 어떻게 왜 어디다가 쓰는건가!








<br>

* 참고로 몽고디비는 빌드하고나서 아래와 같이 참조하여 라이브러리를 사용한다.
  * (출처) - http://cheonbrave.blogspot.kr/2017/06/mongodb-c-driver-1.html


>그럼 컴파일할때 어떻게 참조 하나요 ? 
만약 C 로 코딩해서 test.c 라는 소스를 작성했다고 했을 때 
아래와같이 수행하면 됩니다. 

        gcc -o test test.c -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/libbson-1.0 -L/usr/local/lib/ -L/usr/lib64 -lmongoc-1.0 -lbson-1.0 
 
* 그렇다면 설치한 cassandra c driver 라이브러리가 어느 경로에 설치됐는지 알면 되겠지!?

