PAV - P2: detección de actividad vocal (VAD)
============================================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 2](https://github.com/albino-pav/P2),
y una parte de su gestión se realizará mediante esta web de trabajo colaborativo.  Al contrario que Git,
GitHub se gestiona completamente desde un entorno gráfico bastante intuitivo. Además, está razonablemente
documentado, tanto internamente, mediante sus [Guías de GitHub](https://guides.github.com/), como
externamente, mediante infinidad de tutoriales, guías y vídeos disponibles gratuitamente en internet.


Inicialización del repositorio de la práctica.
----------------------------------------------

Para cargar los ficheros en su ordenador personal debe seguir los pasos siguientes:

*	Abra una cuenta GitHub para gestionar esta y el resto de prácticas del curso.
*	Cree un repositorio GitHub con el contenido inicial de la práctica (sólo debe hacerlo uno de los
	integrantes del grupo de laboratorio, cuya página GitHub actuará de repositorio central del grupo):
	-	Acceda la página de la [Práctica 2](https://github.com/albino-pav/P2).
	-	En la parte superior derecha encontrará el botón **`Fork`**. Apriételo y, después de unos segundos,
		se creará en su cuenta GitHub un proyecto con el mismo nombre (**P2**). Si ya tuviera uno con ese 
		nombre, se utilizará el nombre **P2-1**, y así sucesivamente.
*	Habilite al resto de miembros del grupo como *colaboradores* del proyecto; de este modo, podrán
	subir sus modificaciones al repositorio central:
	-	En la página principal del repositorio, en la pestaña **:gear:`Settings`**, escoja la opción 
		**Collaborators** y añada a su compañero de prácticas.
	-	Éste recibirá un email solicitándole confirmación. Una vez confirmado, tanto él como el
		propietario podrán gestionar el repositorio, por ejemplo: crear ramas en él o subir las
		modificaciones de su directorio local de trabajo al repositorio GitHub.
*	En la página principal del repositorio, localice el botón **Branch: master** y úselo para crear
	una rama nueva con los primeros apellidos de los integrantes del equipo de prácticas separados por
	guion (**fulano-mengano**).
*	Todos los miembros del grupo deben realizar su copia local en su ordenador personal.
	-	Copie la dirección de su copia del repositorio apretando en el botón **Clone or download**.
		Asegúrese de usar *Clone with HTTPS*.
	-	Abra una sesión de Bash en su ordenador personal y vaya al directorio **PAV**. Desde ahí, ejecute:

		```.sh
		git clone dirección-del-fork-de-la-práctica
		```

	-	Vaya al directorio de la práctica `cd P2`.
	-	Añada la etiqueta `origin` a su copia del repositorio. Esto es útil para facilitar los *push* y
		*pull* al repositorio original:
		```.sh
		git remote add origin dirección-del-fork-de-la-práctica
		```
	-	Cambie a la rama **fulano-mengano** con la orden:

		```.sh
		git checkout fulano-mengano
		```

*	A partir de este momento, todos los miembros del grupo de prácticas pueden trabajar en su directorio
	local del modo habitual.
	-	También puede utilizar el repositorio remoto como repositorio central para el trabajo colaborativo
		de los distintos miembros del grupo de prácticas; o puede serle útil usarlo como copia de
		seguridad.
	-	Cada vez que quiera subir sus cambios locales al repositorio GitHub deberá confirmar los
		cambios en su directorio local:

		```.sh
		git add .
		git commit -m "Mensaje del commit"
		```

		y, a continuación, subirlos con la orden:

		```.sh
		git push -u origin fulano-mengano
		```

*	Al final de la práctica, la rama **fulano-mengano** del repositorio GitHub servirá para remitir la
	práctica para su evaluación utilizando el mecanismo *pull request*.
	-	Vaya a la página principal de la copia del repositorio y asegúrese de estar en la rama
		**fulano-mengano**.
	-	Pulse en el botón **New pull request**, y siga las instrucciones de GitHub.


Entrega de la práctica.
-----------------------

Responda, en este mismo documento (README.md), los ejercicios indicados a continuación. Este documento es
un fichero de texto escrito con un formato denominado _**markdown**_. La principal característica de este
formato es que, manteniendo la legibilidad cuando se visualiza con herramientas en modo texto (`more`,
`less`, editores varios, ...), permite amplias posibilidades de visualización con formato en una amplia
gama de aplicaciones; muy notablemente, **GitHub**, **Doxygen** y **Facebook** (ciertamente, :eyes:).

En GitHub. cuando existe un fichero denominado README.md en el directorio raíz de un repositorio, se
interpreta y muestra al entrar en el repositorio.

Debe redactar las respuestas a los ejercicios usando Markdown. Puede encontrar información acerca de su
sintáxis en la página web [Sintaxis de Markdown](https://daringfireball.net/projects/markdown/syntax).
También puede consultar el documento adjunto [MARKDOWN.md](MARKDOWN.md), en el que se enumeran los
elementos más relevantes para completar la redacción de esta práctica.

Recuerde realizar el *pull request* una vez completada la práctica.

Ejercicios
----------

### Etiquetado manual de los segmentos de voz y silencio

- Etiquete manualmente los segmentos de voz y silencio del fichero grabado al efecto. Inserte, a 
  continuación, una captura de `wavesurfer` en la que se vea con claridad la señal temporal, el contorno de
  potencia y la tasa de cruces por cero, junto con el etiquetado manual de los segmentos.

  <img src="/img/img1.png" width="1200" align="center">

  Si comparamos la forma de la "curva de potencia" observamos que se estanca en sitios clasificados como
  silencio.
  Aportación: hemos adaptado la práctica 1 para que genere 4 ficheros: uno para la potencia, amplitud,
  tasa de cruces por cero y uno con los tres valores en columnas distintas. (ver en "Trabajos de
  Ampliación")


- A la vista de la gráfica, indique qué valores considera adecuados para las magnitudes siguientes:

	* Incremento del nivel potencia en dB, respecto al nivel correspondiente al silencio inicial, para
	  estar seguros de que un segmento de señal se corresponde con voz.

	  El incremento del nivel de potencia es aproximadamente de 15 dB

	* Duración mínima razonable de los segmentos de voz y silencio.

	<img src="/img/img2.png" width="50" align="center">

	En esta señal, la duración mínima de silencio es de 0.2925 segundos y la de voz es de 1.097.

	<img src="/img/img3.png" width="1200" align="center">
	
	<img src="/img/img4.png" width="1200" align="center">



	* ¿Es capaz de sacar alguna conclusión a partir de la evolución de la tasa de cruces por cero?

	Observamos que la tasa de cruces por cero aumenta en los tiempos de silencio, por lo que deducimos que
	se comporta en función de la frecuencia. Comprobamos que cuando el sonido es fricativo, aumenta la
	frecuencia y por tanto la tasa de cruces por cero también lo hace. Asimismo sucede lo mismo a la
	inversa con los sonidos sonoros (la voz). Al encontrarse con un sonido sonoro, como la frecuencia
	queda considerablemente disminuida, la tasa de cruces por cero disminuye. En el caso de no tener
	sonido vemos que la tasa de cruces por cero se queda en un punto medio entre los dos anteriores casos.

	La desventaja es que para los sonidos sordos, que si se consideran pertenecientes a tramas de voz, se
	detectan como silencio.


### Desarrollo del detector de actividad vocal

- Complete el código de los ficheros de la práctica para implementar un detector de actividad vocal tan
  exacto como sea posible. Tome como objetivo la maximización de la puntuación-F `TOTAL`.

- Inserte una gráfica en la que se vea con claridad la señal temporal, el etiquetado manual y la detección
  automática conseguida para el fichero grabado al efecto. 

<img src="/img/img5.png" width="1200" align="center">


En la imagen superior vemos de abajo arriba: el índice temporal, el archivo .wav en forma de waveform, en 
vad generado con nuestro código y finalmente en la parte superior el .lab que generamos nosotros con el
etiquetado manual.

- Explique, si existen. las discrepancias entre el etiquetado manual y la detección automática.

Hay discrepancias ya que el código a veces detecta como silencio partes de voz sorda. pero todos los 
tramos de silencio los detecta bien. Es verdad que con esta señal el resultado no se observa con claridad, 
ya que tiene mucho ruido ocasional de fondo, pero en general pensamos que la detección es mejorable, 
aunque el resultado es aceptable.

- Evalúe los resultados sobre la base de datos `db.v4` con el script `vad_evaluation.pl` e inserte a 
  continuación las tasas de sensibilidad (*recall*) y precisión para el conjunto de la base de datos (sólo
  el resumen).

  <img src="/img/img6.png" width="1200" align="center">

  Observamos que el resultado obtenido es del 90.436% por lo que menos del 10% de las tramas han sido mal
  detectadas.


### Trabajos de ampliación

#### Adaptación P1
Hemos modificado el código de la primera práctica p1.c para que nos devuelva 4 ficheros: uno para la
potencia, amplitud, tasa de cruces por cero y uno con los tres valores en columnas distintas. A
continuación mostramos los cambios realizados:

Hemos creado 4 variables de ficheros de salida:
```c
FILE *fpOut;
FILE *fpPower;
FILE *fpAmp;
FILE *fpZCR;
```

Escribimos con el siguiente código en los ficheros:
```c
trm = 0;
fpOut = fopen("resultados.txt", "w");
fpPower = fopen("power.txt", "w");
fpZCR = fopen("zcr.txt", "w");
fpAmp = fopen("amp.txt", "w");

fprintf(fpOut,"\tPotencia media(dB):\tAmplitud media:\tTasa de cruces por cero:\n");
while (lee_wave(buffer, sizeof(*buffer), N, fpWave) == N) {
    for (int n = 0; n < N; n++) x[n] = buffer[n] / (float) (1 << 15);

    fprintf(fpOut,"%d\t%f\t\t\t%f\t\t%f\n", trm, compute_power(x, N),
    compute_am(x, N),
    compute_zcr(x, N, fm));
    fprintf(fpPower,"%f\n",compute_power(x,N));
    fprintf(fpZCR,"%f\n",compute_zcr(x, N, fm));
    fprintf(fpAmp,"%f\n",compute_am(x, N));
    trm += 1;
}
```

Cerramos los ficheros:
```c
fclose(fpOut);
fclose(fpPower);
fclose(fpZCR);
fclose(fpAmp);
```

#### Resultados con una nueva señal
Como la señal grabada inicialmente, en la P1, no se distinguían muy bien las tramas de voz y de sonido, ya
que contenía mucho ruido ocasional de fondo y las palabras tenían poco espacio de silencio entre ellas, y
que obtuvimos un  buen resultado en la base de datos del db.v4, hemos realizado un nuevo audio en el que
la diferenciación de tramas de silencio y voz se vean más claras.

Para la nueva señal, que hemos denominado “PAV_2301_01.wav”, observamos como los espacios entre tramas de
voz y silencio están más diferenciados, lo cual nos ayudará a la hora de observar los resultados obtenidos.

<img src="/img/img7.png" width="1200" align="center">

El resultado obtenido es el siguiente:

<img src="/img/img8.png" width="1200" align="center">

Observamos que en esta señal se aprecia mejor la similitudes de los ficheros de transcripción, y que en
algunas tramas funciona de manera muy eficaz. A vista, parece ser que al programa le cuesta más
diferenciar cuando se termina una trama de voz, y pasa a ser silencio, que a la inversa.

#### Cancelación del ruido en los segmentos de silencio

- Si ha desarrollado el algoritmo para la cancelación de los segmentos de silencio, inserte una gráfica en
  la que se vea con claridad la señal antes y después de la cancelación (puede que `wavesurfer` no sea la
  mejor opción para esto, ya que no es capaz de visualizar varias señales al mismo tiempo).

#### Gestión de las opciones del programa usando `docopt_c`

- Si ha usado `docopt_c` para realizar la gestión de las opciones y argumentos del programa `vad`, inserte
  una captura de pantalla en la que se vea el mensaje de ayuda del programa.


### Contribuciones adicionales y/o comentarios acerca de la práctica

- Indique a continuación si ha realizado algún tipo de aportación suplementaria (algoritmos de detección o 
  parámetros alternativos, etc.).

- Si lo desea, puede realizar también algún comentario acerca de la realización de la práctica que
  considere de interés de cara a su evaluación.


### Antes de entregar la práctica

Recuerde comprobar que el repositorio cuenta con los códigos correctos y en condiciones de ser 
correctamente compilados con la orden `meson bin; ninja -C bin`. El programa generado (`bin/vad`) será
el usado, sin más opciones, para realizar la evaluación *ciega* del sistema.
