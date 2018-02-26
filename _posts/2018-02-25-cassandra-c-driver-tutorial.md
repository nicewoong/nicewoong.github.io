---
layout:     post
title:      "Cassandra(카산드라) C 드라이버 설치 튜토리얼"
subtitle:   "Cassandra C Driver install" 
date:       2018-02-24 12:00:00
categories: [development]
author:     "nicewoong"
tags:       [development, linux, c, language, programming, c++, library, cassandra]
comments: true
---



<br>
### 참고 링크
* [공식 설명 문서(v2.8) - DataStax C/C++ Driver for Apache Cassandra](https://docs.datastax.com/en/developer/cpp-driver/2.8/topics/)
* [cpp-drivere 우분투 v2.8 다운로드 서버](http://downloads.datastax.com/cpp-driver/ubuntu/16.04/cassandra/v2.8.1/)
* [cpp-driver 우분투 디펜던시 다운로드 서버(최신거)](http://downloads.datastax.com/cpp-driver/ubuntu/16.04/dependencies/)  


<br>


* 위 서버로 접속하면 cpp-driver 도 그렇고, dependancies 도 그렇고 모두 .deb 파일이 올라가 있다. 

* 그럼 이걸 어쩌란 말인가? 

* 그리고 디펜던시는 도대체 뭐 어쩌라고 올려두는건가? 

* 디펜던시도 다운받아야 하는건가? 그럼 그걸 어떻게 왜 어디다가 쓰는건가!

* 위 다운로드 서버에 접속하면 .deb 파일로 다운로드할 파일들이 있다.





<br>
### `.deb` 파일이란?

* `.deb`은 데비안의 소프트웨어 패키지 포맷의 확장자
* 패키지 관리 시스템 
* 데비안 소프트웨어 포맷의 `바이너리 패키지`에서 가장 자주 사용되는 파일 이름이다.
* 데비안 패키지는 데비안 기반의 `GNU`/리눅스 배포판 (`우분투` 등)에서 동작한다.



#### deb 파일 설치

        # dpkg -i [deb파일]


#### 패키지 삭제

        # dpkg -r [패키지 이름]


#### 설치된 패키지 검색

        # dpkg -l





<br>

### CLI에서 URL 을 통해 `.deb`파일 다운받기.
* `.deb` 파일이 무엇인지 알겠다. 

* 그렇다면 위의 카산드라 c 드라이버 다운로드 서버에서 `.deb` 파일을 다운받아보자.

* 어떻게?

* url경로를 통해 파일을 다운로드 할 땐 `wget` or `lftpget` or `curl`명령어를 사용한다. 

* `wget`은 간단하게 특정 url에 있는 파일을 다운로드 할 수 있는 어플리케이션

* 우선 `wget`을 이용해보자. 


* cassandra-cpp-driver 를 먼저 단운로드 한다. 
  * (링크) - [cpp-drivere 우분투 v2.8 다운로드 서버](http://downloads.datastax.com/cpp-driver/ubuntu/16.04/cassandra/v2.8.1/)

        $ sudo wget http://downloads.datastax.com/cpp-driver/ubuntu/16.04/cassandra/v2.8.1/cassandra-cpp-driver_2.8.1-1_amd64.deb

* url 은 위 다운로드 서버에서 해당 파일을 오른쪽 클릭해서 링크를 얻어왔다.

* 아 근데 `...-dbg` 랑 `...-dev` 파일도 있는데 이것들 다 다운로드 해야하는 건가?

* 위 명령어를 통해서 다운로드 하면 현재 폴더에 `.deb`파일이 다운로드 된 것을 확인 가능


        $ ls
        cassandra-cpp-driver_2.8.1-1_amd64.deb

* 그리고 `dpkg`를 통해 설치를 시도해봤는데 안 된다....

* 일단 Cassandra-cpp-driver패키지와 cpp-driver-dependancies 에 있는 것들 세 가지씩 모두 다운 받았다. 

        $ ls -l
        -rw-r--r-- 1 root root  419554 Feb 15 02:48 cassandra-cpp-driver_2.8.1-1_amd64.deb
        -rw-r--r-- 1 root root 8651010 Feb 15 02:48 cassandra-cpp-driver-dbg_2.8.1-1_amd64.deb
        -rw-r--r-- 1 root root  535830 Feb 15 02:48 cassandra-cpp-driver-dev_2.8.1-1_amd64.deb
        -rw-r--r-- 1 root root   60990 Feb 15 02:48 libuv_1.18.0-1_amd64.deb
        -rw-r--r-- 1 root root  197746 Feb 15 02:48 libuv-dbg_1.18.0-1_amd64.deb
        -rw-r--r-- 1 root root   80032 Feb 15 02:48 libuv-dev_1.18.0-1_amd64.deb


* 하.. 그냥 docker 로 ubuntu 하나 새로 팠다. 아마 패키지가 꼬였는 거 같은데 어떻게 해결 방법을 찾을라면 막막해서...
* 다시 위 파일들을 다운받고. 
* `dpkg`를 통해 설치를 시도했는데 아래와 같은 오류가 발생

        # dpkg -i cassandra-cpp-driver_2.8.1-1_amd64.deb 
        Selecting previously unselected package cassandra-cpp-driver.
        (Reading database ... 5073 files and directories currently installed.)
        Preparing to unpack cassandra-cpp-driver_2.8.1-1_amd64.deb ...
        Unpacking cassandra-cpp-driver (2.8.1-1) ...
        dpkg: dependency problems prevent configuration of cassandra-cpp-driver:
         cassandra-cpp-driver depends on libuv; however:
          Package libuv is not installed.

* libuv 가 필요하다고 한다. 다운받은 패키지를 설치하면 되는걸까?
* 그렇다. libuv 파일을 `dpkg`를 통해 설치하고나서 cpp-driver를 설치하니깐 에러 없이 순식간에 끝이났다. 

        # dpkg -i cassandra-cpp-driver_2.8.1-1_amd64.deb 
        (Reading database ... 5083 files and directories currently installed.)
        Preparing to unpack cassandra-cpp-driver_2.8.1-1_amd64.deb ...
        Unpacking cassandra-cpp-driver (2.8.1-1) over (2.8.1-1) ...
        Setting up cassandra-cpp-driver (2.8.1-1) ...
        Processing triggers for libc-bin (2.23-0ubuntu10) ...



* 아 근데 우분투에 너무 아무것도 설치가 안 돼 있다...

        # apt-get install vim
        # apt-get install gcc
        # apt-get install net-tools
        # apt-get install g++
        # apt-get install openssh-client openssh-server
        # apt-get install python
        # apt-get install git
        # apt-get install build-essential
        



* vi 설정도 해줬음. `vi ~/.vimrc`를 통해 설정파일을 열어 아래 것들을 입력해준다.

        set number          
        set ai                  
        set si                   
        set cindent           
        set shiftwidth=4     
        set tabstop=4        
        set ignorecase      
        set hlsearch         
        set expandtab      
        set background=dark 
        set nocompatible   
        set fileencodings=utf-8,euc-kr    
        set bs=indent,eol,start   
        set history=1000    
        set ruler             
        set nobackup    
        set title             
        set showmatch    
        set nowrap 
        set wmnu          
        syntax on  


* 또 기본 세팅 더 해주자. 추후에. 
  * https://blog.shako.net/ubuntu-server-16-04-initial-setup-guide/







* `test.c `를 만들어서 `#include <cassandra.h>` 를 포함시켜서 컴파일 해봤다. 
* 에러가 발생했다. `cassandra.h`를 찾을 수 없단다. 
* 경로를 지정해줘야하는건가?
* 그래서 아래 명령어로 `cassandra-cpp-driver~.deb` 파일을 설치했을 때 만들어낸 파일 목록을 펼쳐봤다. 

        # dpkg -c cassandra-cpp-driver_2.8.1-1_amd64.deb 
        drwxr-xr-x root/root         0 2018-02-14 16:14 ./
        drwxr-xr-x root/root         0 2018-02-14 16:14 ./usr/
        drwxr-xr-x root/root         0 2018-02-14 16:14 ./usr/share/
        drwxr-xr-x root/root         0 2018-02-14 16:14 ./usr/share/doc/
        drwxr-xr-x root/root         0 2018-02-14 16:14 ./usr/share/doc/cassandra-cpp-driver/
        -rw-r--r-- root/root       845 2018-02-14 16:11 ./usr/share/doc/cassandra-cpp-driver/copyright
        -rw-r--r-- root/root       212 2018-02-14 16:11 ./usr/share/doc/cassandra-cpp-driver/changelog.Debian.gz
        drwxr-xr-x root/root         0 2018-02-14 16:14 ./usr/lib/
        drwxr-xr-x root/root         0 2018-02-14 16:14 ./usr/lib/x86_64-linux-gnu/
        -rw-r--r-- root/root   1535928 2018-02-14 16:14 ./usr/lib/x86_64-linux-gnu/libcassandra.so.2.8.1
        lrwxrwxrwx root/root         0 2018-02-14 16:14 ./usr/lib/x86_64-linux-gnu/libcassandra.so.2 -> libcassandra.so.2.8.1 


* 그리고 서버에서 다운받은 모든 cpp-driver 의 .dep 파일을 모두 설치해줫다! 그러니깐 일딴 cassandra.h 를 인클루듷 ㅏ는 것은 문제 없었따. 
* 하지만 test 코드에서 사용된 함수들을 못찾겠다고 컴파일 에러...;

        # gcc test.c
        /tmp/ccBWYYkU.o: In function `main':
        test.c:(.text+0xe): undefined reference to `cass_cluster_new'
        test.c:(.text+0x1c): undefined reference to `cass_session_new'
        test.c:(.text+0x31): undefined reference to `cass_cluster_set_contact_points'
        test.c:(.text+0x44): undefined reference to `cass_session_connect'
        test.c:(.text+0x54): undefined reference to `cass_future_error_code'
        test.c:(.text+0x61): undefined reference to `cass_error_desc'
        test.c:(.text+0x7f): undefined reference to `cass_future_free'
        test.c:(.text+0x8b): undefined reference to `cass_session_free'
        test.c:(.text+0x97): undefined reference to `cass_cluster_free'

* 검색하다가... 아래와 같이 입력했더니 컴파일은 완료 되었다. 

        # gcc test.c -o test -L/usr/lib/ -lcassandra
        
* 아니 근데.. usr/lib 는 기본 참조 디렉터리라서 라이브러리경로 명시안해줘도 되는 줄 알았는데!?? ㅠㅠ

* test 실행파일을 실행하면 아래와 같이 출력이 된다. 근데 connect result에 아무것도 출력 안 된다..;

        # ./test 
        Connect result: 

* 그렇다. 이것은 성공한 것이었다. 쿼리하는 코드를 추가해보니 잘 적용이 됐다 .하하. 굿~








* Installation 설명에 아래와 같이 적혀있는데, 무슨 뜻이지!!!????

> Note: CentOS and Ubuntu use the version of OpenSSL provided with the distribution.










<br>
### 기타
-----


* 참고로 몽고디비는 빌드하고나서 아래와 같이 참조하여 라이브러리를 사용한다.
  * (출처) - http://cheonbrave.blogspot.kr/2017/06/mongodb-c-driver-1.html


>그럼 컴파일할때 어떻게 참조 하나요 ? 
만약 C 로 코딩해서 test.c 라는 소스를 작성했다고 했을 때 
아래와같이 수행하면 됩니다. 

        gcc -o test test.c -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/libbson-1.0 -L/usr/local/lib/ -L/usr/lib64 -lmongoc-1.0 -lbson-1.0 
 
* 그렇다면 설치한 cassandra c driver 라이브러리가 어느 경로에 설치됐는지 알면 되겠지!?

