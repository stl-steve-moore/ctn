/*
 * CompositeDialogBox.java
 *
 * Created on February 26, 2001, 2:11 PM
 */


/**
 *
 * @author  smm
 * @version 
 */

import DICOM.*;
import java.util.Vector;
/*import javax.swing.JTable; */

public class CompositeDialogBox extends javax.swing.JDialog {

    /** Creates new form CompositeDialogBox */
    public CompositeDialogBox(java.awt.Frame parent,boolean modal) {
        super (parent, modal);
        initComponents ();
        pack ();
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the FormEditor.
     */
    private void initComponents() {//GEN-BEGIN:initComponents
        jScrollPane1 = new javax.swing.JScrollPane();
        getContentPane().setLayout(new java.awt.GridLayout(1, 1));
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                closeDialog(evt);
            }
        }
        );
        
        
        getContentPane().add(jScrollPane1);
        
    }//GEN-END:initComponents

    /** Closes the dialog */
    private void closeDialog(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_closeDialog
        setVisible (false);
        dispose ();
    }//GEN-LAST:event_closeDialog

    /**
    * @param args the command line arguments
    */
    public static void main (String args[]) {
        new CompositeDialogBox (new javax.swing.JFrame (), true).show ();
    }

    public void renderDICOM(DICOM.DICOMWrapper w) {
        java.util.Vector titles = new java.util.Vector(3,1);
        titles.addElement("Tag");
        titles.addElement("Description");
        titles.addElement("Value");
        
        int tags[] = w.linearizeAttributes();
        int tagCount = tags.length;
        java.util.Vector rowData = new java.util.Vector(tagCount,1);
        java.lang.Integer xInt = new java.lang.Integer(1);
        for (int i = 0; i < tagCount; i++) {
            int tag = tags[i];
            String x1 = xInt.toString(tag, 16);
            while(x1.length() < 8) {
                x1 = '0' + x1;
            }
            String x3 = w.getString(tag);
            
            java.util.Vector rowx = new java.util.Vector(3,1);
            rowx.addElement(x1);
            rowx.addElement("z");
            rowx.addElement(x3);
            rowData.addElement(rowx);
        }
        
        javax.swing.JTable tbl = new javax.swing.JTable(rowData, titles);
        jScrollPane1.setViewportView(tbl);
        tbl.setVisible(true);
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JScrollPane jScrollPane1;
    // End of variables declaration//GEN-END:variables

}
