# CMI4200L-Handler
CMSI4200L-Handler S/W Source - LG Innotek
<br/><br/>

### System Requirements

* Supported Operating System <br/>
  ```
  Windows 7 / x86
  ```

* Application Build <br/>
  ```
  Windows 10 / x64
  ```
  
### Prerequisite

* **Install**
  
  - EzSoftware UC
  ```
  C:\Program Files (x86)\EzSoftware UC
  ```

### Project Settings

* **Include**

  ```
	Include;
	%(AdditionalIncludeDirectories)
  ```
  
* **Library**

  ```
	Library;
	%(AdditionalLibraryDirectories)
  ```
  
### Runtime Requirements
  
* **Settings**

  ```
  System INI & Setting Files  - D:\CMI4200L\Run\System
                                    - D:\CMI4200L\Run\Model
  ```
  
* **Log & Result Files**

  Log Files
  ```
  Handler Log                -  D:\CMI4200L\Run\Log\Handler
  Alarm Log                -  D:\CMI4200L\Run\Log\Alarm
  JobList Log                -  D:\CMI4200L\Run\Log\JobList
  Inspector Log                -  D:\CMI4200L\Run\Log\Inspector
  MESAgent Log                -  D:\CMI4200L\Run\Log\MesAgent
  LotData Log                -  D:\CMI4200L\Run\Log\LotData
  MES Log                - D:\MES\LOG
  ECM Log                - D:\EVMS\TP\LOG
  ```
  

