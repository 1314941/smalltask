package com.qst.dms.entity;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

public class AppendObjectOutputStream extends ObjectOutputStream {

	public AppendObjectOutputStream(FileOutputStream os) throws IOException {
		super(os);
	}

	protected void writeStreamHeader() throws IOException {
		super.reset();
	}

	/*
	 * public static ObjectOutputStream newInstance(String f) throws
	 * FileNotFoundException, IOException { File file = new File(f); if
	 * (file.length() == 0) { return new ObjectOutputStream(new
	 * FileOutputStream(file)); } else { return new AppendObjectOutputStream(new
	 * FileOutputStream(file)); } }
	 */

}
