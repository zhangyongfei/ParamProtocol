FUNCTION(AddLibDirs PATHLIST)
    LIST(LENGTH ARGV argc)
    SET(i 0)
	WHILE(i LESS ${argc})	    
	    LIST(GET ARGV ${i} argvalue)  
        LINK_DIRECTORIES(${argvalue})
		MATH(EXPR i "${i} + 1")
    ENDWHILE()    
ENDFUNCTION(AddLibDirs)

FUNCTION(AddLibDirsWin32 DEFS)
IF(WIN32)
    LIST(LENGTH ARGV argc)
    SET(i 0)
	WHILE(i LESS ${argc})	    
	    LIST(GET ARGV ${i} argvalue)  
        LINK_DIRECTORIES(${argvalue})
		MATH(EXPR i "${i} + 1")
    ENDWHILE()  
ENDIF()
ENDFUNCTION(AddLibDirsWin32)

FUNCTION(AddLibDirsLinux DEFS)
IF(UNIX AND NOT APPLE)
    LIST(LENGTH ARGV argc)
    SET(i 0)
	WHILE(i LESS ${argc})	    
	    LIST(GET ARGV ${i} argvalue)  
        LINK_DIRECTORIES(${argvalue})
		MATH(EXPR i "${i} + 1")
    ENDWHILE()  
ENDIF()
ENDFUNCTION(AddLibDirsLinux)

FUNCTION(AddLibDirsOsx DEFS)
IF(APPLE)
    LIST(LENGTH ARGV argc)
    SET(i 0)
	WHILE(i LESS ${argc})	    
	    LIST(GET ARGV ${i} argvalue)  
        LINK_DIRECTORIES(${argvalue})
		MATH(EXPR i "${i} + 1")
    ENDWHILE()  
ENDIF()
ENDFUNCTION(AddLibDirsOsx)

FUNCTION(AddLibDirsAndroid DEFS)
IF(UNIX AND NOT APPLE AND NOT CYGWIN)
    LIST(LENGTH ARGV argc)
    SET(i 0)
	WHILE(i LESS ${argc})	    
	    LIST(GET ARGV ${i} argvalue)  
        LINK_DIRECTORIES(${argvalue})
		MATH(EXPR i "${i} + 1")
    ENDWHILE()  
ENDIF()
ENDFUNCTION(AddLibDirsAndroid)

#------------------------------------------------------------------

FUNCTION(AddLibs LIBSLIST LIBS)
    SET(TMPLIST)
	LIST(LENGTH ARGV argc)
    SET(i 1)
	WHILE(i LESS ${argc})	    
	    LIST(GET ARGV ${i} argvalue)  
        SET(TMPLIST "${TMPLIST};${argvalue}")
		MATH(EXPR i "${i} + 1")
    ENDWHILE()
	LIST(GET ARGV 0 argvalue) 
	IF("X${${argvalue}}" STREQUAL "X")
	    SET(${LIBSLIST} "${TMPLIST}" PARENT_SCOPE)
	ELSE()
	    SET(${LIBSLIST} "${${argvalue}};${TMPLIST}" PARENT_SCOPE)
	ENDIF()
ENDFUNCTION(AddLibs)

FUNCTION(AddLibsWin32 LIBSLIST LIBS)
IF(WIN32)
    SET(TMPLIST)
	LIST(LENGTH ARGV argc)
    SET(i 1)
	WHILE(i LESS ${argc})	    
	    LIST(GET ARGV ${i} argvalue)  
        SET(TMPLIST "${TMPLIST};${argvalue}")
		MATH(EXPR i "${i} + 1")
    ENDWHILE()
	LIST(GET ARGV 0 argvalue) 
	IF("X${${argvalue}}" STREQUAL "X")
	    SET(${LIBSLIST} "${TMPLIST}" PARENT_SCOPE)
	ELSE()
	    SET(${LIBSLIST} "${${argvalue}};${TMPLIST}" PARENT_SCOPE)
	ENDIF()
ENDIF()
ENDFUNCTION(AddLibsWin32)

FUNCTION(AddLibsLinux LIBSLIST LIBS)
IF(UNIX AND NOT APPLE)
    SET(TMPLIST)
	LIST(LENGTH ARGV argc)
    SET(i 1)
	WHILE(i LESS ${argc})	    
	    LIST(GET ARGV ${i} argvalue)  
        SET(TMPLIST "${TMPLIST};${argvalue}")
		MATH(EXPR i "${i} + 1")
    ENDWHILE()
	LIST(GET ARGV 0 argvalue) 
	IF("X${${argvalue}}" STREQUAL "X")
	    SET(${LIBSLIST} "${TMPLIST}" PARENT_SCOPE)
	ELSE()
	    SET(${LIBSLIST} "${${argvalue}};${TMPLIST}" PARENT_SCOPE)
	ENDIF()
ENDIF()
ENDFUNCTION(AddLibsLinux)

FUNCTION(AddLibsApple LIBSLIST LIBS)
IF(APPLE)
    SET(TMPLIST)
	LIST(LENGTH ARGV argc)
    SET(i 1)
	WHILE(i LESS ${argc})	    
	    LIST(GET ARGV ${i} argvalue)  
        SET(TMPLIST "${TMPLIST};${argvalue}")
		MATH(EXPR i "${i} + 1")
    ENDWHILE()
	LIST(GET ARGV 0 argvalue) 
	IF("X${${argvalue}}" STREQUAL "X")
	    SET(${LIBSLIST} "${TMPLIST}" PARENT_SCOPE)
	ELSE()
	    SET(${LIBSLIST} "${${argvalue}};${TMPLIST}" PARENT_SCOPE)
	ENDIF()
ENDIF()
ENDFUNCTION(AddLibsApple)

FUNCTION(AddLibsAndroid LIBSLIST LIBS)
IF(UNIX AND NOT APPLE AND NOT CYGWIN)
    SET(TMPLIST)
	LIST(LENGTH ARGV argc)
    SET(i 1)
	WHILE(i LESS ${argc})	    
	    LIST(GET ARGV ${i} argvalue)  
        SET(TMPLIST "${TMPLIST};${argvalue}")
		MATH(EXPR i "${i} + 1")
    ENDWHILE()
	LIST(GET ARGV 0 argvalue) 
	IF("X${${argvalue}}" STREQUAL "X")
	    SET(${LIBSLIST} "${TMPLIST}" PARENT_SCOPE)
	ELSE()
	    SET(${LIBSLIST} "${${argvalue}};${TMPLIST}" PARENT_SCOPE)
	ENDIF()
ENDIF()
ENDFUNCTION(AddLibsAndroid)