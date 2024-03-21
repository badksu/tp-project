
<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="content-type" content="text/html; charset=utf-8"/>
	<title></title>
	<meta name="generator" content="LibreOffice 7.3.7.2 (Linux)"/>
	<meta name="created" content="00:00:00"/>
	<meta name="changed" content="2024-03-13T20:43:21.327910118"/>
	<style type="text/css">
		@page { size: 8.27in 11.69in; margin: 1in }
		p { line-height: 115%; text-align: left; orphans: 2; widows: 2; margin-bottom: 0.1in; direction: ltr; background: transparent }
	</style>
</head>
<body link="#000080" vlink="#800000" dir="ltr"><p align="center" style="margin-bottom: 0in">
<font face="Liberation Mono, monospace"><font size="4" style="font-size: 14pt"><b>Архитектура
проекта</b></font></font></p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">Имеется
класс Game, за счет которого происходит
весь процесс игры. В его полях находятся
2 игрока. Основной метод - play(), в нем
происходит процесс игры. Игроки по
очереди делают золы, пока не будет найден
winner с помощью метода getWinner()</font></font></p>
<p style="margin-bottom: 0in"><br/>

</p>
<p align="center" style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt"><b>Сущности</b></font></font></p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt"><b>Ship</b></font></font></p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">В
полях корабля хранятся его размер,
позиция его начала, сет из его &quot;живых&quot;
клеток, направление и состояние. Начальное
состояние - ALIVE. </font></font>
</p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">При
попадании в клетку корабля, эта клетка
удаляется из сета, состояние сменяется
на DAMAGED. Когда сет становится пуст,
состояние меняется на DESTROYED.</font></font></p>
<p style="margin-bottom: 0in"><br/>

</p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt"><b>Field</b></font></font></p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">Поле
хранит в себе двумерный массив field,
массив  кораблей, счетчик живых кораблей.
Ячейки двумерного массива кодируются
следующим образом: field[I][j] = -1, если клетка
поля пустая, field[I][j] = -2, если в пустую
ячейку поля стреляли, field[I][j] &gt; -1, если
эта клетка - клетка корабля, в ячейке
лежит номер этого корабля в массиве
кораблей. </font></font>
</p>
<p style="margin-bottom: 0in"><br/>

</p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt"><b>OwnField</b></font></font></p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">Это
- некоторая &quot;обертка&quot; над Field самого
игрока, чтобы он мог пользоваться своим
полем так, как предполагается в игре. В
OwnField хранится ссылка на Field данного
игрока.</font></font></p>
<p style="margin-bottom: 0in"><br/>

</p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt"><b>OpponentsField</b></font></font></p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">Это
- некоторая &quot;обертка&quot; над Field
противника, чтобы игрок мог проводить
действия с полем противка. В OpponentsField
хранится ссылка на Field противника.</font></font></p>
<p style="margin-bottom: 0in"><br/>

</p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt"><b>Player</b></font></font></p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">Игрок
хранит в себе свое имя, OwnField и OpponentsField.
 Имеется метод - initSelf(), в нем игрок вводит
свое имя и расставляет корабли на своем
поле. Основной метод - makeMove(), с помощью
него игрок делает ход.  В этом методе
игрок выбирает, хочет ли он просмотреть
текущее состояние своего поля, поля
противника, или желает сразу делать
выстрел. </font></font>
</p>
<p style="margin-bottom: 0in"><br/>

</p>
<p align="center" style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="4" style="font-size: 14pt"><b>Обоснование
архитектуры</b></font></font></p>
<p style="margin-bottom: 0in"><br/>

</p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">Хотелось
бы, чтобы совершению выстрела игроком,
в поле его противника автоматически
происходили изменения. Иными словами,
хотелось бы не передавать координаты
выстрела из одного экземпляра Player в
другой. Именно для этого мы &quot;оборачиваем&quot;
новым классом OwnField и OpponentsField, которые
хранят ссылки на тот участок памяти,
что соответствует обычным полям игроков.
Таким образом, при завершении выстрела
вызывается opponentsField.shootInCell(...) {
field-&gt;shootInCell(...); }, противник в своем поле
автоматически увидет выстрел, его не
придется передавать для изменения поля
после выстрела.</font></font></p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">Так
же благодаря данным &quot;оберткам&quot;
игроки могут делать только те действия
со своим полем и полем противника,
которые предполагаются в игре. А именно:
игрок может только стрелять в поле
противника, узнавать количество живых
кораблей только в своем поле. При
просмотре своего поля игрок видит свои
корабли и выстрелы, которые сделал
противник. При просмотре поля противника
игрок видит только свои выстрелы. </font></font>
</p>
<p style="margin-bottom: 0in"><br/>

</p>
<p style="margin-bottom: 0in"><br/>

</p>
<p align="center" style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="4" style="font-size: 14pt"><b>Расположение
проекта</b></font></font></p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">Проект
находится в директории SeaBattle. В
SeaBattle/include находятся заголовочные файлы
ship.h, field.h, player.h, game.h, которые хранят
объявления соответствующих сущностей.
В SeaBattle/src хранятся соответствующие cpp
файлы.</font></font></p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">В
SeaBattle/info хранятся UML диаграммы, сценарии
использования и описание архитектуры(данное
описание).</font></font></p>
<p align="center" style="margin-bottom: 0in"><br/>

</p>
<p align="center" style="margin-bottom: 0in"><br/>

</p>
<p align="center" style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="4" style="font-size: 14pt"><b>Запуск</b></font></font></p>
<p style="margin-bottom: 0in"><font face="Liberation Mono, monospace"><font size="3" style="font-size: 12pt">Запускается
проект с помощью следующих команд:</font></font></p>
<p style="margin-bottom: 0in"><br/>

</p>
</body>
</html>
