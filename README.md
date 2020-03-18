# URL Parser

## General Info
Designed to parse a URL and extract the protocol, domain, port, file path, and parameters. The format of these components can be found at https://developer.mozilla.org/en-US/docs/Learn/Common_questions/What_is_a_URL .

## URL Components
1. Acceptable Protocols: hhtp, https, ftp, ftps
2. Domain: Must be of the form <x>.<y>.<z>, and z must be one of com, net, edu, biz, gov.
    * Note: strictly speaking this component is called ‘host’.
3.	Port: starts with the ‘:’ character and a number between 1 to 65535. 
    * This component is optional.
4.	File path: must start with a ‘/’ and end with ‘.html’ or ‘.htm’. 
5.	Parameters: starts with the ‘?’ character, e.g. ?name=Bob. This component is optional.

## Input Validation
If the conditons above were not satisfied, the InvalidURL flag will be set and the user will be asked to enter a new URL.
