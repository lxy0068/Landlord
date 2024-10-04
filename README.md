

![landlord-bk](README/landlord-bk.png)



# 1. 游戏部署

## 1.1 开发环境

1. 平台：Windows，Qt是跨平台的其他平台应该也是没问题的。
2. IDE：QtCreator
3. Qt版本要求：5.10 及以上版本
   - 开发该项目使用的Qt版本：`5.15.2`，其他版本可能会出现二进制资源文件（xxx.rcc）无法加载的问题。
   - 不要使用 Qt6（使用的多媒体类在Qt6中已经不存在了）
4. 使用的编译套件：MinGW
   - 使用 MSVC 编译套件应该也可以，但可能会出现乱码（可自测）

## 1.2 关于资源文件的部署

1. 使用 `QtCreator` 打开项目文件 `Landlords.pro`，编译并生成可执行程序。

2. 关于资源文件的加载：

   - 使用`QtCreator`启动程序

     将项目目录中的资源文件`resource.rcc`拷贝到生成的`build`目录下即可，build 目录名示例：`build-Landlords-Desktop_Qt_5_15_2_MinGW_32_bit-Debug`

   - 直接双击`.exe`可执行文件启动程序

     将项目目录中的资源文件`resource.rcc`拷贝到和`.exe`文件同级目录即可。

   - 如果使用的编译套件是 MSVC，资源文件直接放到可执行程序`.exe`对应的目录中。

3. 游戏效果图

   ![33333](README/33333.png)

   ![](README/3434.png)

   


# 2. 游戏规则

<font color="red">不同地域游戏规则可能有些许差异，游戏按照如下规则进行实现。</font>

## 2.1 牌型

|    牌型    |                   描述                   |
| :--------: | :--------------------------------------: |
|    王炸    |           大王+小王，最大的牌            |
|    炸弹    |         四张同数值牌（如四个 9）         |
|    单牌    |          单张的牌（如红桃 3 ）           |
|    对牌    |  数值相同的两张牌（如梅花 4+ 方块 4 ）   |
|   三张牌   |      数值相同的三张牌（如三个 Q ）       |
|   三带一   | 数值相同的三张牌 + 1张单牌，例如： 333+6 |
|   三带二   | 数值相同的三张牌 + 1对牌，例如： 666+33  |
|    顺子    |  五张或更多的连续单牌，不包括 2 和双王   |
|    连对    |  三对或更多的连续对牌，不包括 2 和双王   |
|    飞机    | 二个或更多的连续三张牌，不包括 2 和双王  |
| 飞机带翅膀 |   飞机＋同数量的单牌（或同数量的对牌）   |
|   四带二   | 四张点数相同的牌 + 两手牌 （两单或两双） |
|  王炸带二  |       王炸 + 两手牌 （两单或两双）       |



## 2.2 牌型的大小

- 王炸最大，可以压任意其他的牌型。
- 炸弹比王炸小，比其它牌型大。都是炸弹时按牌的点数比大小。

- 除火箭和炸弹外，其它牌必须要牌型相同且总数量相同才能比大小。

- 单牌按点数比大小（不分花色），依次是：

  `大王 > 小王 > 2 > A > K > Q > J > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 `

- 对牌，三张点数相同的牌都按点数比大小。

- 顺子按最大的一张牌的点数来比大小。

- 飞机带翅膀和四带二按其中的三顺和四张部分来比，带的副牌不参与牌型大小的比较。



## 2.3 游戏角色

参与游戏的玩家一共需要三个人，这三个人有两种角色，分别是：

- 地主：1人，三人下注抢地主，分数最高者可称为地主，地主自己一伙。
- 农民：2人，没有抢到地主的玩家为农民，此二人一伙。



## 2.4 游戏规则

1. **发牌**

   一副牌 54 张，一人 17 张，留 3 张做底牌，在确定地主之前玩家不能看到底牌。

2. **叫地主 / 抢地主**

   - 叫地主按出牌的顺序轮流进行，每人只能叫一次。
   - 叫地主时可以叫 “1 分 ” ， “2 分 ” ， “3 分 ” ， “ 不叫 ” 。
   - 后抢地主者只能叫比前面玩家高的分或者不叫。
   - 抢地主结束后下注分值最大的玩家为地主；如果有玩家叫 “3 分 ” 则立即结束叫地主，该玩家为地主；如果都不叫，则重新发牌，重新叫地主。

3. **第一轮叫地主的玩家**

   - 由于是单机版斗地主，直接指定了用户玩家为第一个叫地主的玩家
   - 也可以由系统随机选定

4. **出牌**

   - 将三张底牌交给地主，并亮出底牌让所有人都能看到。
   - 地主首先出牌，然后按逆时针顺序依次出牌，轮到用户跟牌时，用户可以选择 “ 不出 ” 或出比上一个玩家大的牌。
   - 某一玩家出完牌时结束本局。

   

## 2.5 游戏的胜负

任意一家出完牌后结束游戏，先出完牌的玩家代表的角色获胜：

- 地主先出完牌地主获胜
- 任意一个农民先出完牌则农民获胜



## 2.6 游戏计分规则

- 底分：叫地主时的下注分数，可下注分数分别为：1分、2分、3分。
- 倍数：初始为 1 ，每出一个炸弹或王炸翻一倍（留在手上没出的不算）。

当一局游戏结束后，基于低分和倍数计算个玩家得分：

- 地主胜：
  - 地主：`2 * 底分 * 倍数`
  - 农民：`- 底分 * 倍数`
- 农民胜：
  - 地主：`-2 * 底分 * 倍数`
  - 农民：`底分 * 倍数`

`在实现的游戏代码中，没有处理春天的情况（一个玩家牌已出完，另外两个玩家的牌一张未出），如若需要，可自行添加。`



# 3. 其他

欢迎关注作者：

个人博客：https://subingwen.cn

B站个人主页：https://space.bilibili.com/147020887

微信公众号：ibc_dabing