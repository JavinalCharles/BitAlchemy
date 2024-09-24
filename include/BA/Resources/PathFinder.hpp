#pragma once

#include <filesystem>
#include <iostream>
#include <optional>
#include <vector>

namespace ba {
namespace Resources {
	namespace fs = std::filesystem;

	/**
	 * @brief PathFinder is a helper class for searching the file system
	 * for files or directories.
	 * 
	 * PathFinder is intended to be the base class for all specialization
	 * of the template class ResourceManager and provides a uniform way of
	 * searching for Resources, though the class could also be used as is.
	 * 
	 * @remark The class PathFinder got its name from a popular tabletop
	 * adventure-RPG game of the same name, and as well as a couple of 
	 * video games based on that tabletop game.
	 */
	class PathFinder {
		/// TODO: Add a method or two for recursive directory search.
	public:
		/// @brief default constructor
		PathFinder();

		virtual ~PathFinder();

		/// @{
		/**
		 * @brief Adds a path to the list of paths available only to
		 * this instance of PathFinder.
		 * 
		 * Attempts to add a path to this PathFinder instance's list
		 * of search paths, provided that p satisfies the following 
		 * criteria:
		 * 	- p can be an absolute path or a relative path.
		 * 		- if p is a relative path, it will be considered a
		 * 			a child path of current working directory or
		 * 			any of the paths in the common search paths.
		 * 	- p must exist
		 * 		
		 * 
		 * @param p The path to be added.
		 * @return true if p is successfully added, otherwise false.
		 */
		int addPath(const std::string& p);
		int addPath(const fs::path& p);
		/// @}

		///@{
		/**
		 * @brief Adds a path p to the list of common paths available to
		 * all instances of PathFinder.
		 * 
		 * Attempts to add p to the list of common paths available for
		 * access by any and all instances and subtypes of PathFinder.
		 * p must satisfy the following criteria to be added.
		 * 	- p can either be an absolute or relative path.
		 * 		- 	if relative, the function will treat p as if it is a
		 * 			subdirectory of current working directory.
		 * 	- p must exist.
		 *  - p must be end with a directory, not a file 
		 * p will be added if these criterias are satisfied.
		 * 
		 * @param p The path to be added.
		 * @returns true if the p is successfully added, otherwise false.
		 */
		static bool addCommonPath(const std::string& p);
		static bool addCommonPath(const fs::path& p);
		///@}

		///@{
		/**
		 * @brief searches the search paths for filePath.
		 * 
		 * Provided that filePath is a relative path, and has a file
		 * name, this checks for the existence of filePath relative to any
		 * of the search paths associated with this PathFinder, and if none
		 * is found, checks the common search Paths for the same. The
		 * function will return the first instance of filePath found, or 
		 * std::nullopt.
		 * 
		 * If filePath is an absolute path, then the function only checks
		 * if filePath has a file name and if it exists before returning
		 * it or std::nullopt.
		 * 
		 * @param filePath The file to search for.
		 * @returns The absolute path to filePath, provided it exists.
		 * Otherwise, std::nullopt.
		 */
		std::optional<fs::path> findFile(const std::string& filePath) const;
		std::optional<fs::path> findFile(const fs::path& filePath) const;
		///@}

		///@{
		/**
		 * @brief Searches all search paths for instances of filePath
		 * 
		 * The function searches all the search paths associated with this
		 * PathFinder object and the static common search paths, for any
		 * and all instances of filePath, provided that filePath is a
		 * relative path and has a file name.
		 * 
		 * If filePath is an absolute path, the function will only check 
		 * for if filePath has a file name and exists, and returns a vector
		 * with one element if it does, otherwise an empty vector.
		 * 
		 * If filePath has no file name, or no filePath exists in all the
		 * search paths, then the function will return an empty vector.
		 * 
		 * @param filePath the file to search for.
		 * @returns an array of existing absolute paths that ends in 
		 * filePath.
		 */
		std::vector<fs::path> findAllFiles(const std::string& filePath) const;
		std::vector<fs::path> findAllFiles(const fs::path& filePath) const;
		///@}
	protected:
		/// @brief search paths associated with this PathFinder instance.
		std::vector<fs::path>			m_paths;
		/// @brief search paths accessible to all PathFinder instance.
		static std::vector<fs::path>	s_commonPaths;
	}; // class PathFinder

} // namespace Resources
} // namespace ba