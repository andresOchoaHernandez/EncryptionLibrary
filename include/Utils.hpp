/**
 * @file Utils.hpp
 * @author Andres Ochoa Hernandez
 * @brief This file contains utility functions common to all the modules in the project
 */

#pragma once

#include <string>

/**
 * @brief Adds a specifed padding character to a string or truncates it if needed, depending on the numberOfBytes specified
 * @param str Original string
 * @param numberOfBytes The number of bytes that have to be reached
 * @param paddingChar The character used for padding
 * @returns A string of numberOfBytes bytes
 */
std::string padString(const std::string& str, size_t numberOfBytes,char paddingChar);

/**
 * @brief Generates a string of a specified number of bytes
 * @param length The desired length of the string
 * @returns A string of length bytes
 */
std::string generateRandomString(size_t length);