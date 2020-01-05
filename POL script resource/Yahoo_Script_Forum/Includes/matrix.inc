/* MATRIX INCLUDE (Class for you C++ lovers)

	Written by: Joshua Nighthawk
	Date: 3-3-02
	Version: .1 - First public release

	Usage:
		MakeMatrix(entries, r := 0, c := 0)

		Entries is an array of the entries you want. Example:
		  MakeMatrix({1, 2, "NLCR", 3}) would make matrix:
		    [1 2]
		    [3 0]
		Put in "NLCR" to start a new row. If you want the entire matrix to be
		  one entry, set the first entry to be "SetAllToNextValue" and be sure
		  to pass r (rows) and c (columns). Example:
		    MakeMatrix({"SetAllToNextValue", 5}, 3, 3) would make matrix:
		      [5 5 5]
		      [5 5 5]
		      [5 5 5]
		MakeMatrix() returns a matrix variable, which is an array of arrays..


		numRows(matrix)

		Returns the number of rows. Example:
		  var mtx := MakeMatrix({"SetAllToNextValue", 3}, 3, 5);
		  var rows := numRows(mtx);
		rows would be 3.


		numCols(matrix)

		Returns the number of columns. Example:
		  var mtx := MakeMatrix({5, 5, 9, "NLCR", 1, 2});
		  var cols := numCols(mtx);
		cols would be 3.


		SetStandard(matrix)

		This is mostly called from the MakeMatrix() function, but you can use it.
		It standardizes an array to have 0s where there are empty spaces. Example:

		  var mtx := array(array(3, 5),array(1));
		    mtx would be:
		      [3 5]
		      [1  ]
		  SetStandard(mtx);
		    mtx now becomes:
		      [3 5]
		      [1 0]
		It returns a message depending on success. MakeMatrix() prints it to console by default.

	Please send any feedback, suggestions, or bug reports to Shadow808@aol.com.

	To be added in next version;
	  insertRow(after, array);
	  insertCol(after, array);

*/

use uo;
use os;
use basic;

function numRows(byref matrix)
	return  matrix.size();
endfunction

function SetStandard(byref matrix)
	local entry;
	local longest := 0;
	foreach entry in matrix
		if(entry.size() > longest)
			longest := entry.size();
		endif
	endforeach
	foreach entry in matrix
		if(entry.size() > longest)
			return "Error in SetStandard() in Matrix class!";
		elseif(entry.size() < longest)
			entry.shrink(longest);
		endif
	endforeach
	return "Matrix standardized.";
endfunction

function numCols(byref matrix2)
	Print(SetStandard(matrix2));
	return matrix2[1].size();
endfunction

function MakeMatrix(entries, r := 0, c := 0)
	local entry;
	local rows := 1;
	local cols := 0;
	local col := 0;
	local matrix := array(array);
	local i;
	local ii;
	foreach entry in entries
		if(lower(entries[1]) = "setalltonextvalue" and !col)
			for(i := 1 ; i <= r ; i := i + 1)
				matrix.append(array);
				for(ii := 1 ; ii <= c ; ii := ii + 1)
					matrix[ii].append(entries[2]);
				endfor
			endfor
			col := 1;
		elseif(entry = "NLCR" and lower(entries[1]) != "setalltonextvalue")
			matrix.append(array);
			rows := rows + 1;
			col := 1;
		elseif(lower(entries[1]) != "setalltonextvalue")
			matrix[rows].append(entry);
			if(!col)
				cols := cols + 1;
			elseif(matrix[rows].size() > cols)
				cols := matrix[rows].size();
			endif
		endif
	endforeach
	Print(SetStandard(matrix));
	return matrix;
endfunction