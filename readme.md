
<h1> How to build</h1>

To build: run build.bat or build.sh depends of your OS.

<h1> Architecture ( How it works ) </h1>
In main function file accepted by C++ iostream.
Then a stream passed to  TSReader class which split MPEG-TS stream to packets and feed it to MPEG_PacketProcessor.<br/>
TSReader class is templated by two classes: container and processor, for two purposes:<br/>
<ol>
<li> Fasilitate unit testing by mocking template parameters. ( You can easily replace template parameter by your mock class)</li>
<li> Demonstrate ability to work with templates :) </li>
</ol>
When the MPEG_PacketProcessor object accept MPEG_TSPacket it ask PayloadProcessorFactory for proper PayloadProcessor. <br/>
PayloadprocessorFactory implemeted as singleton and Functional Factory. <br/>
New processor for new payload types can be easily registered in factory without changing the PayloadProcessorFactory code.<br/>
Base class for audio and video processors implements Curiously Recurring Template Pattern: <br/>
https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern <br/>
To avoid duplication of code.
