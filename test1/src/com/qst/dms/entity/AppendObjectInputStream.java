package com.qst.dms.entity;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

public class AppendObjectInputStream extends ObjectInputStream {
	public AppendObjectInputStream(FileInputStream in) throws IOException {
		super(in);
	}

	protected void readStreamHeader() {

	}
}
