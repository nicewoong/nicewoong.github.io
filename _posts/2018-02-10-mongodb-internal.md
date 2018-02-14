---
layout:     post
title:      "MongoDB 구조 "
subtitle:   "MongoDB internal" 
date:       2018-02-10 12:00:00
categories: [development]
author:     "nicewoong"
tags:       [development, mongodb, database, nosql, shard, sharding]
comments: true
---


# 몽고디비의 내부 구조 (Mongodb internal )

<br>
## Storage Engine 의 종류 
* WierdTiger (3.2 default)
  * Many CPU, Lots of RAM 에 효과적
* MMAPv1 (3.0 default)


## (1) MMAPv1 스토리지엔진의 구조 

<br>
### DB internal structure

<img src="{{ site.url }}/assets/mongodb_internal_structure.png" alt="mongodb_internal_structure" style="width:600px" />

* MongoDB의 데이터 저장소는 메모리 맵 파일(Memory Mapped File)을 사용한 가상 메모리를 사용한다

* 몽고디비의 데이터 구조는 데이터를 저장하는 Record , 인덱스를 저장하는 Bucket. 
  * **Record** : BSON 객체를 저장하는 노드를 레코드로 정의 
  * MongoDB는 BSON 객체를 데이터 저장 단위로 사용
  * BSON 객체의 이중연결리스트 (double linked list)구조로 구성
  * **Bucket** : 인덱스는 레코드에 저장된 데이터를 빠르게 찾기 위해 b-tree 형태로 저장된 노드 구조를 가짐
  * b-tree 노드를 버켓(Bucket)이라고 정의

* **Extent** : MongoDB는 대용량 데이터를 HDD에 쉽게 저장할 수 있는 단위로 레코드들을 그룹핑grouping한다.
  * 이를 익스텐드extent라고 한다
  * 익스텐드들을 이용하여 MongoDB는 HDD에 저장될 파일과 삭제된 레코드를 관리한다.
  * 자료 구조 관점에서 보면 연결되어 있는 레코드들의 헤더 역할을 수행하는 것

* 사용자가 하나의 데이터베이스를 만들었다면, MongoDB는 데이터베이스와 관련된 한 개의 **네임스페이스(DB Namespace)**를 만든다.
* DB Namespace는 **컬렉션 (collection Namespace)** 와
**Free Extent 리스트**(DB에서 삭제된 레코드 리스트를 가지고 있는 Extent 리스트)를 가진다. 
* Collection Namespace는 primary index Namespace(B Tree)와 Record Extent list를 가진다. 
* 만약 Primary index 이외에 추가로 필드를 가지고 인덱스를 더 생성하면 B Tree 형태의 Index Namespace를 하나 더 가진다.


* Write(insert/update)를 수행할 때,  MongoDB는 해당 레코드가 가리키는 가상 메모리 주소 공간에 데이터를 적재한다.
* Read를 수행할 때, MongoDB는 해당 메모리 주소 공간에 할당된 데이터가 가상 메모리에 로딩되어 있는지 확인하고, 
없다면 파일에서 내용을 읽어 가상 메모리에 적재한다.
* MongoDB는 백그라운드로 (주기적으로)가상 메모리에 적재된 데이터를 HDD에 최대 2GB 단위로 파일을 구성한 볼륨(volume)으로
HDD에 데이터를 flush한다.





<br>
### Record Structure 
<img src="{{ site.url }}/assets/mongo_record_structure.png" alt="mongo_record_structure"/>


* 헤더는 총 16바이트 크기
* 데이터는 도큐멘트를 BSON 객체 형태로 가진다.
  * Size : 헤더를 포함하고 있는 레코드의 크기, 
BSON 객체의 크기는 Size 필드에서 헤더 크기인 16을 빼면 된다.
  * Extent Offset : 해당 레코드가 속해 있는 익스텐트(Extent)의 Offset 주소 
    * (MongoDB는 모든 위치를 DiskLoc이라는 구조체를 사용
    * volume 정보와 offset 정보 두 개를 가지는 구조체. 
    * 여기서 말하는 offset은 DiskLoc의 offset 주소와 동일)
  * Next Offset : 다음 레코드를 가리키는 Offset 주소
  * bson object : 도큐멘트를 구성하는 BSON 객체

* 참고 : Document의 크기는 Field 명을 포함하므로 필드명을 길게하고 하면 데이터가 많아질 수록 Document 크기가 커진다





<br>
### Extent Structure 
<img src="{{ site.url }}/assets/mongo_extent_structure.png" alt="mongo_extent_structure" />


* MongoDB의 Extent는 Record들의 그룹을 말한다.
* 헤더 4바이트와 데이터 172바이트로 구성 (총 178바이트의 크기)
  * Magic : 4바이트 헤더이며, 정수 781231 값을 가진다.
  * My Location: 해당 Extent가 저장된 위치 정보를 나타낸다.
  * Next Extent : 다음 Extent를 가리킴  
  * Prev Extent : 이전 Extent를 가리킴
  * Namespace : 해당 Extent의 네임 스페이스
  * Size : 해당 익스텐드의 크기
  * First Record : 해당 Extent에 포함된 첫번째 레코드를 가리킴
  * Last Record : 해당 Extent에 포함된 마지막 레코드를 가리킴

* My Location, Next Extent, Prev Extent, First Record, Last Record 
  * 들은 모두 8바이트 크기를 가지고 있다. 
  * 64비트 컴퓨터의 주소는 64비트 크기를 가지고 있기 때문에 8바이트 크기를 가진다. 
  * 그리고 size 필드가 4바이트로 규정되어 있다.
  * MSBMost Significant Bit 를 제외하면 2GB의 크기 까지 익스텐트의 크기를 지정할 수 있다. 

* MongoDB는 로컬 스토리지에 데이터베이스 명으로 확장자가 숫자로 증분하는 형태의 파일을 가진다. 
  * 예를 들어 test.1이라고 하면, test라는 데이터베이스의 첫번째 익스텐트를 의미한다.

<br>
## (2) WierdTiger 스토리지엔진 구조 
* ...공부예정... 




<br><br>
## 참고

* [몽고디비 데이터 구조 ](http://mongodb.citsoft.net/ )
* [mongodb internals (Slide Share )](https://www.slideshare.net/NorbertoLeite/mongodb-internals-55965341)
* [A Technical Introduction to WiredTiger(Slide Sahre)](https://www.slideshare.net/wiredtiger/mongo-db-worldwiredtiger?next_slideshow=1)
* [Inside MongoDB: the Internals of an Open-Source Database(Slide Share )](https://www.slideshare.net/mdirolf/inside-mongodb-the-internals-of-an-opensource-database )
* [Practical MongoDB(book)](https://books.google.co.kr/books?id=7iI3CwAAQBAJ&pg=PA166&lpg=PA166&dq=mongodb+b+tree&source=bl&ots=cLtkVTWESk&sig=AqOe913XuVKGOf30YzqpF2QNIBQ&hl=ko&sa=X&ved=0ahUKEwj2vran6rzXAhUMy7wKHVS_AFk4ChDoAQg9MAM#v=onepage&q=mongodb%20b%20tree&f=false)
