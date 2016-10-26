import java.util.Scanner;
import java.io.File;
import java.io.IOException;

import java.awt.image.BufferedImage;
import java.awt.Color;
import java.awt.BorderLayout;
import java.awt.FlowLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.Icon;
import javax.swing.ImageIcon;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/** Display and compare two images in pgm format. */
public class ImageComp implements ActionListener {
  /** Image for the first command-line argument. */
  Icon left;
  
  /** Image for the second command-line argument. */
  Icon right;
  
  /** Image showing the differences between the images in pink. */
  Icon both;
  
  /** Label, for showing the various images. */
  JLabel display;

  private void usage() {
    System.err.printf( "usage: ImageComp <image1.ppm> [image2.ppm]\n" );
    System.exit( 1 );
  }

  /** Read an image from the given file and return it as an image. */
  private BufferedImage loadImage( String filename ) {
    try {
      Scanner input = new Scanner( new File( filename ) );

      // Read the image header.
      String token = input.next();
      if ( ! token.equals( "P3" ) ) {
        System.err.printf( "File %s doesn't look like a PPM file.\n", filename );
        usage();
      }

      int width = input.nextInt();
      int height = input.nextInt();
      int cmax = input.nextInt();
      if ( cmax != 255 ) {
        System.err.printf( "File %s doesn't look like a PPM image in the right format.\n", filename );
        usage();
      }

      // Make an image and populate it with pixel values from the input file.
      BufferedImage img = new BufferedImage( width * 2, height * 2, BufferedImage.TYPE_INT_ARGB );
      for ( int i = 0; i < height; i++ )
        for ( int j = 0; j < width; j++ ) {
          int r = input.nextInt();
          int g = input.nextInt();
          int b = input.nextInt();
          int c = new Color( r, g, b ).getRGB();
          img.setRGB( j * 2, i * 2, c );
          img.setRGB( j * 2, i * 2 + 1, c );
          img.setRGB( j * 2 + 1, i * 2, c );
          img.setRGB( j * 2 + 1, i * 2 + 1, c );
        }


      input.close();

      return img;
    } catch ( IOException e ) {
      System.err.printf( "Error reading image from file: %s\n", filename );
      usage();
    }

    return null;
  }

  /** To respond to button presses in the UI. */
  public void actionPerformed( ActionEvent e ) {
    if ( "left".equals( e.getActionCommand() ) )
      display.setIcon( left );
    else if ( "right".equals( e.getActionCommand() ) )
      display.setIcon( right );
    else
      display.setIcon( both );
  }

  /** Process command-line arguments and create UI. */
  private void run( String[] args ) {
    if ( args.length < 1 || args.length > 2 )
      usage();

    // Read the one or two images.
    BufferedImage leftImg, rightImg = null, bothImg = null;
    leftImg = loadImage( args[ 0 ] );
    if ( args.length > 1 ) {
      rightImg = loadImage( args[ 1 ] );

      // Generate the difference image.
      if ( leftImg.getWidth() != rightImg.getWidth() ||
           leftImg.getHeight() != rightImg.getHeight() ) {
        System.err.printf( "Images aren't the same size\n" );
        System.exit( 1 );
      }

      bothImg = new BufferedImage( leftImg.getWidth(), leftImg.getHeight(), BufferedImage.TYPE_INT_ARGB );
      for ( int i = 0; i < leftImg.getHeight(); i++ )
        for ( int j = 0; j < leftImg.getWidth(); j++ ) {
          int a = leftImg.getRGB( j, i );
          int b = rightImg.getRGB( j, i );
          if ( a != b )
            bothImg.setRGB( j, i, Color.PINK.getRGB() );
          else
            bothImg.setRGB( j, i, a );
        }
    }

    // Build the UI.
    JFrame frame = new JFrame( "ImageComp" );
    frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
    frame.setLayout( new BorderLayout() );

    left = new ImageIcon( leftImg );
    display = new JLabel( left );
    frame.add( display, BorderLayout.CENTER );

    // If we have two arguments, make UI controls to switch among the
    // three images.
    if ( args.length > 1 ) {
      JPanel buttons = new JPanel();

      right = new ImageIcon( rightImg );
      both = new ImageIcon( bothImg );

      buttons.setLayout( new FlowLayout() );

      JButton btn = new JButton( args[ 0 ] );
      btn.setActionCommand( "left" );
      btn.addActionListener( this );
      buttons.add( btn );

      // If the press the right-hand button, just show the right-hand image.
      btn = new JButton( args[ 1 ] );
      btn.setActionCommand( "right" );
      btn.addActionListener( this );
      buttons.add( btn );
      
      btn = new JButton( "difference" );
      btn.addActionListener( this );
      buttons.add( btn );

      frame.add( buttons, BorderLayout.NORTH );
    }

    frame.pack();
    frame.setVisible( true );
  }
  
  public static void main( String[] args ) {
    // Make an instance of imagecomp, and run it.  That way, we can
    // have fields if we need them.
    ImageComp comp = new ImageComp();
    comp.run( args );
  }
}
