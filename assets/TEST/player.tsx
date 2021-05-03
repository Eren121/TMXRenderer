<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.5" tiledversion="1.6.0" name="player" tilewidth="32" tileheight="32" tilecount="12" columns="3">
 <image source="player.png" width="96" height="128"/>
 <tile id="0" type="T_Character">
  <properties>
   <property name="class" value="player"/>
   <property name="moving" type="bool" value="true"/>
  </properties>
  <animation>
   <frame tileid="0" duration="100"/>
   <frame tileid="1" duration="100"/>
   <frame tileid="2" duration="100"/>
  </animation>
 </tile>
 <tile id="1" type="T_Character">
  <properties>
   <property name="class" value="player"/>
  </properties>
 </tile>
 <tile id="3" type="T_Character">
  <properties>
   <property name="class" value="player"/>
   <property name="direction" value="left"/>
   <property name="moving" type="bool" value="true"/>
  </properties>
  <animation>
   <frame tileid="3" duration="100"/>
   <frame tileid="4" duration="100"/>
   <frame tileid="5" duration="100"/>
  </animation>
 </tile>
 <tile id="4" type="T_Character">
  <properties>
   <property name="class" value="player"/>
   <property name="direction" value="left"/>
  </properties>
 </tile>
 <tile id="6" type="T_Character">
  <properties>
   <property name="class" value="player"/>
   <property name="direction" value="right"/>
   <property name="moving" type="bool" value="true"/>
  </properties>
  <animation>
   <frame tileid="6" duration="100"/>
   <frame tileid="7" duration="100"/>
   <frame tileid="8" duration="100"/>
  </animation>
 </tile>
 <tile id="7" type="T_Character">
  <properties>
   <property name="class" value="player"/>
   <property name="direction" value="right"/>
  </properties>
 </tile>
 <tile id="9" type="T_Character">
  <properties>
   <property name="class" value="player"/>
   <property name="direction" value="up"/>
   <property name="moving" type="bool" value="true"/>
  </properties>
  <animation>
   <frame tileid="9" duration="100"/>
   <frame tileid="10" duration="100"/>
   <frame tileid="11" duration="100"/>
  </animation>
 </tile>
 <tile id="10" type="T_Character">
  <properties>
   <property name="class" value="player"/>
   <property name="direction" value="up"/>
  </properties>
 </tile>
</tileset>
