# Release note details

## Version 0 (preview version)

### Version 0.1.0

#### Main goal of version

First implementation with draft interfaces and no configuration for customisation

#### Features of version

- generated technical documentation (doxygen)
- convert cppcheck issues report to sonaqube generic data issue report
- convert clang-tidy (plain text) issues report to sonaqube generic data issue report
- packaging for each 3 main operating systems (Linux, Windows, Mac)

#### Issues in version

- exit status in error case is 0 like success

### Version 0.2.0

#### Main goal of version

Convert Boost Test reports to Sonarqube with generic format

#### Features of version

- add Boost test result report conversion
- add Boost test log report conversion
- add unit tests for all reports
- add manual in readme
- add description file in cpack configuration
- add icon app in cpack configuration
- add --version, -v options in cli
- add --help, -h options in cli

### Version 0.3.0

#### Main goal of version

Add GCC and MSVC warning reports capacity

#### Features of version

- add vcpkg manifest
- add compile option in CMakeLists.txt
- add RPM packaging
- add generated web page for deployments
- add Readme in doxygen home pages
- add GCC warning reports
- add MSVC warning reports
- fix column start

#### Main goal of version

Add logger and configuration
### Version 0.4.0 (planning)

- add icon app in cpack configuration (part 2)
- add summary after report conversion
- fix sonar issues
- add clang-tidy json entry format meanplace of plain text report format (proof of concept)
- add configuration to change severity of rule, change type, disable rule
- add file and std::cout/cerr logger (external component)
