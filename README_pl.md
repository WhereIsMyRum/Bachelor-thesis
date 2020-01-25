<html>
<body>
<h1 class="title">Monitoring Muscle Activity</h1>
<h3 class="why">Powód</h3>
<p class="why">Niniejsza aplikacja powstała w ramach mojej pracy inżynierskiej. Pełny tytuł pracy brzmiał: "System do monitorowania przebiegu ćwiczeń siłowych w oparciu o analizę biopotencjałów". Za samą pracę jak i jej obronę otrzymałem ocenę bardzo dobrą, i dzięki temu, jak również dzięki całokształowi moich osiągnięć podczas studiów, otrzymałem dyplom z wyróznieniem. </p>
<h3 class="what">Cel</h3>
<p class="what">Celem było stworzenie systemu, który pozwalałby użytkownikowi monitorować przebieg jego ćwiczeń siłowych. Niniejszy projekt jest niejako "proof of concept" całego pomysłu - umozliwia monitorowanie i detekcję skurcza mięśnia dwugłowego ramienia podczas uginania ramienia ze sztangielką stojąc. U podstaw systemu leży eletromiografia (EMG) -  technika diagnostyczna umożliwiająca rejestrownaie aktywności elektrycznej mięśnia podczas jego skurczu.</p>
<h3 class="how">Wykonane</h3>
<p class="how">Sensor EMG jest umieszczany w centralnej części mięśnia dwugłowego ramienia osoby badanej. Sensor ten (MyoWare Muscle Sensor) mierzy aktywnością elektryczną mieśnia, wzmacnia ją i wytwarza w ten sposób wzmocniony analogowy sygnał wyjściowy. Sygnał ten jest następnie przetwarzany na sygnał cyfrowy przy użyciu płytki Arduino Leonardo, poprzez równomiernie próbkowanie z częstotliwością 1GHz. Następnie sygnał jest przesyłany przez USB to aplikacji desktopowej napisaniej przy wykorzystaniu C++ oraz Qt, która rysuje wykres zależności napięcia w czasie, oraz zapisuje wyniki w pliku tekstowym. Wykonano serię pomiarów na kilkunastu osobach, następnie wszystkie zebrane dane zostały ręcznie oznakowane i wykorzystane w procesie uczenia klasyfikatora opartego na Maszynie Wektorów Nośnych (Support Vector Machine, SVM). Pozwala to na klasfyikowanie sygnału w czasie rzeczywistym przy wykorzystaniu prostokątnego okna o szerokości 500ms i wykrycie, kiedy użytkownik wykonuje skurcz w trakcie ćwiczenia, a kiedy jego mięsień znajduje się w stanie spoczynku.</p>
<h3 class="technologies">Zastosowane technologie</h3>
<ul class="technologies">
  <li class="technologies" hover="C++">C++</li>
  <li class="technologies" hover="C">C</li>
  <li class="technologies" hover="Qt">Qt</li>
  <li class="technologies" hover="Arduino">Arduino</li>
  <li class="technologies" hover="Support Vector Machine">SVM</li>
</ul>
<h3 class="thesis">Praca</h3>
<p class="thesis">Zobacz moją pracę inżynierską <a target="_blank" href="https://raw.githubusercontent.com/WhereIsMyRum/Monitoring-muscle-activity/master/thesis.pdf">tutaj</a><</p>
<hr>
<small class="created">Data powstania: Wrzesień-Grudzień 2017</small>
</body>
</html>
