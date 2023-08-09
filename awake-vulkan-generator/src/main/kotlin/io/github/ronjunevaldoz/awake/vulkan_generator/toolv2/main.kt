/*
 * Awake
 * Awake.awake-vulkan-generator.main
 *
 * Copyright (c) ronjunevaldoz 2023.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package io.github.ronjunevaldoz.awake.vulkan_generator.toolv2

import io.github.ronjunevaldoz.awake.vulkan_generator.toolv2.builder.CppClassBuilder

fun cppClass(
    className: String,
    fileDescription: String,
    block: CppClassBuilder.() -> Unit
): String {
    val builder = CppClassBuilder(className, fileDescription)
    builder.block()
    return builder.build()
}

fun main() {
    val cppClassCode = cppClass("Person", "This is a sample C++ header file") {
        import("<iostream>")
        import("<string>")
        import("<vector>")

        member("private", "std::string", "name")
        member("public", "int", "age")
        member("protected", "char", "gender")

        function<Unit>(1, "exampleForLoop") {
            body(2) {
                child("for (int i = 0; i < 5; ++i) {")
                child("    std::cout << \"Loop iteration \" << i << std::endl;")
                child("}")
            }
        }

        function<Int>(1, "exampleAddNumbers", Pair("a", ""), Pair("b", "")) {
            body(2) {
                child("return a + b;")
            }
        }
    }
//    val cppInterfaceCode = cppInterface("Person", "Interface for Person class.") {
//        interfaceMethod("interfaceMethod", String::class, Pair("param1", Int::class)) // Define interface method
//    }

    println(cppClassCode)
//    println(cppInterfaceCode)
}