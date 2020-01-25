<html>
<body>
<h1 class="title">Monitoring Muscle Activity</h1>
<h3 class="why">Why</h3>
<p class="why">This app was created for my Bachelor of Engineering thesis. The full title of the project was "System for monitoring of strength training based on biopotential analysis". For both the project and the project's defence I got an A, and becuase of it, as well as because of my performance during the whole study cycle, I was awarded a Honors Diploma.</p>
<h3 class="what">What</h3>
<p class="what">The goal was to create a system that would allow the user to monitor his performance during strength trening. This project is a proof of concept, where the system, in principle, is able to monitor and detect a contraction while the user performs dumbell bicep curls. The system utilizes electromyography (EMG) - a technique for measuring electrical activity of a muscle, that is associated with muscle's contraction.</p>
<h3 class="how">How</h3>
<p class="how">An EMG sensor is placed on the body of a user's bicep. The sensor (MyoWare Muslce Sensor) is capable of measuring the EMG effect, amplify it and produce an analog output signal. The signal is then processed by an Arduino board (Arduino Leonardo), where it is digitalized with a sample frequency of 1 GHz. This signal is then sent through USB to a desktop app, written in C++ and Qt, which plots the registered voltage in time, and saves the output into a text file. &nbsp; A series of measurements was conducted using several test subjects. The output was then labeled and based on it, a Support Vector Machine (SVM) classifier was trained. This allows a real-time signal classification using a rectangular time window, 500ms wide, detecting when the user is performing a contraction, and when he's resting.</p>
<h3 class="technologies">Technologies used</h3>
<ul class="technologies">
  <li class="technologies" hover="C++">C++</li>
  <li class="technologies" hover="C">C</li>
  <li class="technologies" hover="Qt">Qt</li>
  <li class="technologies" hover="Arduino">Arduino</li>
  <li class="technologies" hover="Support Vector Machine">SVM</li>
</ul>
  <h3 class="thesis">Thesis</h3>
  <p class="thesis">Download my thesis here (in polish): <a target="_blank" href="https://raw.githubusercontent.com/WhereIsMyRum/Monitoring-muscle-activity/master/thesis.pdf">click</a></p>
<hr>
<small class="created">Created: September-December 2017</small>
</body>
</html>
