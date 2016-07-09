Pod::Spec.new do |s|
    s.name         = "Kiwi"
    s.version      = '0.1'
    s.summary      = "Kiwi, the efficient cassowary constraint solver."
    s.homepage     = "https://github.com/Nocte-/rhea"
    s.authors      = {
    	"Nocte" => "nocte@hippie.nu"
    	}
    s.license      = 'MIT'
    s.source       = {
        :git => "https://github.com/Nocte-/rhea.git",
        :tag => s.version.to_s
        }
    s.library = 'c++'
    s.xcconfig = {
       'CLANG_CXX_LANGUAGE_STANDARD' => 'c++11',
       'CLANG_CXX_LIBRARY' => 'libc++'
    }
    s.platform      = :ios, '6.0'
    s.requires_arc  = true
    s.source_files  = 'kiwi/kiwi/**/*.{h,hpp,cpp,c,m}'

end
