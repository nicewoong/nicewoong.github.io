---
layout:     post
title:      "리눅스 - make, makefile 이란"
subtitle:   "linux - make, makefile ?" 
date:       2018-02-24 12:00:00
categories: [development]
author:     "nicewoong"
tags:       [development, linux, c, language, programming, c++, library]
comments: true
---


## Make 란?


* `make`는 파일 관리 유틸리티
* 반복적인 명령 자동화를 위한 것.
* `Makefile`이 있는 디렉토리에서 `make` 만 치면 컴파일된다.
* 파일 간의 종속관계를 파악하여 
  `Makefile`( 기술파일 )에 적힌 대로 컴파일러에 명령하여 SHELL 명령 순차적으로 실행
* 프로그램의 종속 구조를 빠르게 파악




<br><br>


## Makefile

* 구조
  * 목적파일(Target) : 명령어가 수행되어 나온 결과를 저장할 파일 
  * 의존성(Dependency) : 목적파일을 만들기 위해 필요한 재료 
  * 명령어(Command) : 실행 되어야 할 명령어들 
  * 매크로(macro) : 코드를 단순화 시키기 위한 방법






<br><br>



## 참고

* [블로그 - 멍멍멍](http://bowbowbow.tistory.com/12#make-와-makefile) <- 설명이 진짜 잘 돼 있음.
