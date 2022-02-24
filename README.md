# DroneProject
#Office Drone Project with Arduino Code

      Statement of the problem:
I work in a big office in Taiwan as a secretary, sometimes feel the document sending back and forth is not that efficiently. It spends lots of time on sending documents and waiting for the financial department’s or accounting department’s confirmation. And the whole document progress might delay and lost on the track.
Image we have a paper document manager drone in an office, and it can provide document delivery and also manage the document progress, we could save more time on tracking or deliver this paper work. In today’s technology, indeed there is an office drone which can provide the security camera and record the office working situation. However, if we can add more function on it and even collect and track the data at the same time, it might can enhance the office work efficiency.

	Software Design- Arduino IDE
I use this for develop the drone is because it can be matched with sensors or peripheral equipment to achieve the purpose of logical automatic control. It also can connect the computer and through the USB square port cable to provide power and a port for computer programming. Arduino also supports a large number of open source hardware, so I can connect various open source hardware to DJI educational drone to achieve various effects, like AI vision sensor or temperature sensor. And Arduino provide data collection environment which can send the data to any database (Mysql) or excel. For this project, I chose Excel to collect the data from the drone and analyze it. 


      Software Design- PLX-DAQ 
Parallax Data Acquisition tool (PLX-DAQ) software add-in for Microsoft Excel acquires up to 26 channels of data from any Parallax microcontrollers and drops the numbers into columns as they arrive. PLX-DAQ provides easy spreadsheet analysis of data collected in the field, laboratory analysis of sensors and real-time equipment monitoring.


     Preface
There are 6 departments will send their request of documents to director. And if the director accepted their document, it would go to next progress which is financial department.
Financial department will verify their document whether it is works or not and also make sure it is not exceeding the budget. Therefore, the financial department will finalize the decision.




