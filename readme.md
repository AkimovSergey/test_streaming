
<h1> How to build</h1>

To build: run build.bat or build.sh depends of your OS.

<h1> Architecture ( How it works ) </h1>

First accept stream StreamParser which split MPEG-TS stream to packets and feed it to MPEG_PacketProcessor.<br/>
Stream parser templated for two purposes:<br/>
<ol>
<li> Fasilitate unit testing by mocking template parameters.</li>
<li> Demonstrate ability to work with templates :) </li>
</ol>
Then MPEG_PacketProcessor ask PayloadProcessorFactory for proper PayloadProcessor. <br/>
PayloadprocessorFactory implemeted as singleton and FunctionalFactory. <br/>
New processor can be easily registered in factory without changing factory code.<br/>
Base class for audio and video processors implements Curiously recurring template pattern: <br/>
https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
