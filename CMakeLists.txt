if(ESP_PLATFORM EQUAL 1)
    if(IDF_VERSION_MAJOR GREATER_EQUAL 4)
        idf_component_register(
            SRCS "Debouncer.cpp"
            INCLUDE_DIRS ".")
    else()
        set(COMPONENT_SRCS "Debouncer.cpp")
        set(COMPONENT_ADD_INCLUDEDIRS ".")
        register_component()
    endif()
endif()
